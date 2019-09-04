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
struct ulp_mem_io {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct cxgbi_task_tag_info {unsigned int idx; unsigned int npods; } ;
struct cxgbi_ppm {unsigned int llimit; int /*<<< orphan*/  lldev; } ;
struct cxgbi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_CONTROL ; 
 int CXGBI_DBG_DDP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPOD_SIZE ; 
 unsigned int PPOD_SIZE_SHIFT ; 
 struct sk_buff* alloc_wr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb3_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_device*,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  ulp_mem_io_set_hdr (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static void ddp_clear_map(struct cxgbi_device *cdev, struct cxgbi_ppm *ppm,
			  struct cxgbi_task_tag_info *ttinfo)
{
	unsigned int idx = ttinfo->idx;
	unsigned int pm_addr = (idx << PPOD_SIZE_SHIFT) + ppm->llimit;
	unsigned int npods = ttinfo->npods;
	int i;

	log_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, clear idx %u, npods %u.\n",
		  cdev, idx, npods);

	for (i = 0; i < npods; i++, idx++, pm_addr += IPPOD_SIZE) {
		struct sk_buff *skb = alloc_wr(sizeof(struct ulp_mem_io) +
					       IPPOD_SIZE, 0, GFP_ATOMIC);

		if (!skb) {
			pr_err("cdev 0x%p, clear ddp, %u,%d/%u, skb OOM.\n",
			       cdev, idx, i, npods);
			continue;
		}
		ulp_mem_io_set_hdr(skb, pm_addr);
		skb->priority = CPL_PRIORITY_CONTROL;
		cxgb3_ofld_send(ppm->lldev, skb);
	}
}