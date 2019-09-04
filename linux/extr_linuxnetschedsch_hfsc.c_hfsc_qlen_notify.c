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
struct hfsc_class {int cl_flags; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int HFSC_RSC ; 
 int /*<<< orphan*/  eltree_remove (struct hfsc_class*) ; 
 int /*<<< orphan*/  update_vf (struct hfsc_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hfsc_qlen_notify(struct Qdisc *sch, unsigned long arg)
{
	struct hfsc_class *cl = (struct hfsc_class *)arg;

	/* vttree is now handled in update_vf() so that update_vf(cl, 0, 0)
	 * needs to be called explicitly to remove a class from vttree.
	 */
	update_vf(cl, 0, 0);
	if (cl->cl_flags & HFSC_RSC)
		eltree_remove(cl);
}