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
struct aa_loaddata {TYPE_1__* ns; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_ns (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_rawdata_dents (struct aa_loaddata*) ; 

void __aa_fs_remove_rawdata(struct aa_loaddata *rawdata)
{
	AA_BUG(rawdata->ns && !mutex_is_locked(&rawdata->ns->lock));

	if (rawdata->ns) {
		remove_rawdata_dents(rawdata);
		list_del_init(&rawdata->list);
		aa_put_ns(rawdata->ns);
		rawdata->ns = NULL;
	}
}