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
struct alias_lcu {struct alias_lcu* uac; struct alias_lcu* rsu_cqr; struct alias_lcu* cpaddr; struct alias_lcu* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct alias_lcu*) ; 

__attribute__((used)) static void _free_lcu(struct alias_lcu *lcu)
{
	kfree(lcu->rsu_cqr->data);
	kfree(lcu->rsu_cqr->cpaddr);
	kfree(lcu->rsu_cqr);
	kfree(lcu->uac);
	kfree(lcu);
}