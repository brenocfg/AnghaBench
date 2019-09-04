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
struct pfn_array_table {int /*<<< orphan*/  pat_pa; } ;
struct channel_program {int /*<<< orphan*/  mdev; } ;
struct ccwchain {struct pfn_array_table* ch_pat; struct ccw1* ch_ccw; } ;
struct ccw1 {scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  count; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_IDA ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 unsigned long* kcalloc (int,int,int) ; 
 int pfn_array_alloc_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_array_table_idal_create_words (struct pfn_array_table*,unsigned long*) ; 
 int pfn_array_table_init (struct pfn_array_table*,int) ; 
 int /*<<< orphan*/  pfn_array_table_unpin_free (struct pfn_array_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (unsigned long*) ; 

__attribute__((used)) static int ccwchain_fetch_direct(struct ccwchain *chain,
				 int idx,
				 struct channel_program *cp)
{
	struct ccw1 *ccw;
	struct pfn_array_table *pat;
	unsigned long *idaws;
	int ret;

	ccw = chain->ch_ccw + idx;

	if (!ccw->count) {
		/*
		 * We just want the translation result of any direct ccw
		 * to be an IDA ccw, so let's add the IDA flag for it.
		 * Although the flag will be ignored by firmware.
		 */
		ccw->flags |= CCW_FLAG_IDA;
		return 0;
	}

	/*
	 * Pin data page(s) in memory.
	 * The number of pages actually is the count of the idaws which will be
	 * needed when translating a direct ccw to a idal ccw.
	 */
	pat = chain->ch_pat + idx;
	ret = pfn_array_table_init(pat, 1);
	if (ret)
		goto out_init;

	ret = pfn_array_alloc_pin(pat->pat_pa, cp->mdev, ccw->cda, ccw->count);
	if (ret < 0)
		goto out_unpin;

	/* Translate this direct ccw to a idal ccw. */
	idaws = kcalloc(ret, sizeof(*idaws), GFP_DMA | GFP_KERNEL);
	if (!idaws) {
		ret = -ENOMEM;
		goto out_unpin;
	}
	ccw->cda = (__u32) virt_to_phys(idaws);
	ccw->flags |= CCW_FLAG_IDA;

	pfn_array_table_idal_create_words(pat, idaws);

	return 0;

out_unpin:
	pfn_array_table_unpin_free(pat, cp->mdev);
out_init:
	ccw->cda = 0;
	return ret;
}