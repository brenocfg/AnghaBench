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
struct dlm_migratable_lockres {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; void* highest_blocked; void* convert_type; void* type; scalar_t__ cookie; } ;
struct dlm_lock {TYPE_1__ ml; int /*<<< orphan*/ * lksb; } ;
struct dlm_ctxt {int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_BLOCKED_LIST ; 
 void* LKM_IVMODE ; 
 int /*<<< orphan*/  dlm_add_lock_to_array (struct dlm_lock*,struct dlm_migratable_lockres*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_lock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dlm_add_dummy_lock(struct dlm_ctxt *dlm,
			       struct dlm_migratable_lockres *mres)
{
	struct dlm_lock dummy;
	memset(&dummy, 0, sizeof(dummy));
	dummy.ml.cookie = 0;
	dummy.ml.type = LKM_IVMODE;
	dummy.ml.convert_type = LKM_IVMODE;
	dummy.ml.highest_blocked = LKM_IVMODE;
	dummy.lksb = NULL;
	dummy.ml.node = dlm->node_num;
	dlm_add_lock_to_array(&dummy, mres, DLM_BLOCKED_LIST);
}