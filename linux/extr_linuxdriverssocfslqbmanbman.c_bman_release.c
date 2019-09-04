#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct bman_portal {int /*<<< orphan*/  p; } ;
struct bman_pool {int /*<<< orphan*/  bpid; } ;
struct bm_rcr_entry {int /*<<< orphan*/ * bufs; } ;
struct bm_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  bufs ;

/* Variables and functions */
 int BM_RCR_VERB_BUFCOUNT_MASK ; 
 int BM_RCR_VERB_CMD_BPID_SINGLE ; 
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  bm_buffer_get64 (struct bm_buffer const*) ; 
 int /*<<< orphan*/  bm_buffer_set64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_buffer_set_bpid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bm_rcr_get_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bm_rcr_pvb_commit (int /*<<< orphan*/ *,int) ; 
 struct bm_rcr_entry* bm_rcr_start (int /*<<< orphan*/ *) ; 
 struct bman_portal* get_affine_portal () ; 
 scalar_t__ likely (struct bm_rcr_entry*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct bm_buffer const*,int) ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_rcr_ci (struct bman_portal*,int) ; 

int bman_release(struct bman_pool *pool, const struct bm_buffer *bufs, u8 num)
{
	struct bman_portal *p;
	struct bm_rcr_entry *r;
	unsigned long irqflags;
	int avail, timeout = 1000; /* 1ms */
	int i = num - 1;

	DPAA_ASSERT(num > 0 && num <= 8);

	do {
		p = get_affine_portal();
		local_irq_save(irqflags);
		avail = bm_rcr_get_avail(&p->p);
		if (avail < 2)
			update_rcr_ci(p, avail);
		r = bm_rcr_start(&p->p);
		local_irq_restore(irqflags);
		put_affine_portal();
		if (likely(r))
			break;

		udelay(1);
	} while (--timeout);

	if (unlikely(!timeout))
		return -ETIMEDOUT;

	p = get_affine_portal();
	local_irq_save(irqflags);
	/*
	 * we can copy all but the first entry, as this can trigger badness
	 * with the valid-bit
	 */
	bm_buffer_set64(r->bufs, bm_buffer_get64(bufs));
	bm_buffer_set_bpid(r->bufs, pool->bpid);
	if (i)
		memcpy(&r->bufs[1], &bufs[1], i * sizeof(bufs[0]));

	bm_rcr_pvb_commit(&p->p, BM_RCR_VERB_CMD_BPID_SINGLE |
			  (num & BM_RCR_VERB_BUFCOUNT_MASK));

	local_irq_restore(irqflags);
	put_affine_portal();
	return 0;
}