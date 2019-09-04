#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct vrfb {int context; scalar_t__* paddr; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OMAP_VRFB_SIZE ; 
 scalar_t__ SMS_ROT_VIRT_BASE (int) ; 
 int /*<<< orphan*/  ctx_lock ; 
 int ctx_map ; 
 TYPE_1__* ctxs ; 
 int /*<<< orphan*/  memset (struct vrfb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_ctxs ; 
 int /*<<< orphan*/  omap_vrfb_release_ctx (struct vrfb*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_bit (int,int*) ; 

int omap_vrfb_request_ctx(struct vrfb *vrfb)
{
	int rot;
	u32 paddr;
	u8 ctx;
	int r;

	DBG("request ctx\n");

	mutex_lock(&ctx_lock);

	for (ctx = 0; ctx < num_ctxs; ++ctx)
		if ((ctx_map & (1 << ctx)) == 0)
			break;

	if (ctx == num_ctxs) {
		pr_err("vrfb: no free contexts\n");
		r = -EBUSY;
		goto out;
	}

	DBG("found free ctx %d\n", ctx);

	set_bit(ctx, &ctx_map);

	memset(vrfb, 0, sizeof(*vrfb));

	vrfb->context = ctx;

	for (rot = 0; rot < 4; ++rot) {
		paddr = ctxs[ctx].base + SMS_ROT_VIRT_BASE(rot);
		if (!request_mem_region(paddr, OMAP_VRFB_SIZE, "vrfb")) {
			pr_err("vrfb: failed to reserve VRFB "
					"area for ctx %d, rotation %d\n",
					ctx, rot * 90);
			omap_vrfb_release_ctx(vrfb);
			r = -ENOMEM;
			goto out;
		}

		vrfb->paddr[rot] = paddr;

		DBG("VRFB %d/%d: %lx\n", ctx, rot*90, vrfb->paddr[rot]);
	}

	r = 0;
out:
	mutex_unlock(&ctx_lock);
	return r;
}