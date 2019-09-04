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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  TCA_EGRESS_MIRROR 131 
#define  TCA_EGRESS_REDIR 130 
#define  TCA_INGRESS_MIRROR 129 
#define  TCA_INGRESS_REDIR 128 

__attribute__((used)) static bool tcf_mirred_act_wants_ingress(int action)
{
	switch (action) {
	case TCA_EGRESS_REDIR:
	case TCA_EGRESS_MIRROR:
		return false;
	case TCA_INGRESS_REDIR:
	case TCA_INGRESS_MIRROR:
		return true;
	default:
		BUG();
	}
}