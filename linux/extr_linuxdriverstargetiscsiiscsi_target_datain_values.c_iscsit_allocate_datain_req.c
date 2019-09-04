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
struct iscsi_datain_req {int /*<<< orphan*/  cmd_datain_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct iscsi_datain_req* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dr_cache ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct iscsi_datain_req *iscsit_allocate_datain_req(void)
{
	struct iscsi_datain_req *dr;

	dr = kmem_cache_zalloc(lio_dr_cache, GFP_ATOMIC);
	if (!dr) {
		pr_err("Unable to allocate memory for"
				" struct iscsi_datain_req\n");
		return NULL;
	}
	INIT_LIST_HEAD(&dr->cmd_datain_node);

	return dr;
}