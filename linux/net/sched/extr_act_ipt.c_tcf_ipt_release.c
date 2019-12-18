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
struct tcf_ipt {scalar_t__ tcfi_tname; scalar_t__ tcfi_t; } ;
struct tc_action {TYPE_1__* idrinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipt_destroy_target (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct tcf_ipt* to_ipt (struct tc_action*) ; 

__attribute__((used)) static void tcf_ipt_release(struct tc_action *a)
{
	struct tcf_ipt *ipt = to_ipt(a);

	if (ipt->tcfi_t) {
		ipt_destroy_target(ipt->tcfi_t, a->idrinfo->net);
		kfree(ipt->tcfi_t);
	}
	kfree(ipt->tcfi_tname);
}