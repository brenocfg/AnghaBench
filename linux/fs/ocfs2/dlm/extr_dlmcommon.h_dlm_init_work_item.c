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
struct dlm_work_item {struct dlm_ctxt* dlm; void* data; int /*<<< orphan*/  list; int /*<<< orphan*/ * func; } ;
struct dlm_ctxt {int dummy; } ;
typedef  int /*<<< orphan*/  dlm_workfunc_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dlm_work_item*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void dlm_init_work_item(struct dlm_ctxt *dlm,
				      struct dlm_work_item *i,
				      dlm_workfunc_t *f, void *data)
{
	memset(i, 0, sizeof(*i));
	i->func = f;
	INIT_LIST_HEAD(&i->list);
	i->data = data;
	i->dlm = dlm;  /* must have already done a dlm_grab on this! */
}