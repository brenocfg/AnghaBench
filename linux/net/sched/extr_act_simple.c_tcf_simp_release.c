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
struct tcf_defact {int /*<<< orphan*/  tcfd_defdata; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct tcf_defact* to_defact (struct tc_action*) ; 

__attribute__((used)) static void tcf_simp_release(struct tc_action *a)
{
	struct tcf_defact *d = to_defact(a);
	kfree(d->tcfd_defdata);
}