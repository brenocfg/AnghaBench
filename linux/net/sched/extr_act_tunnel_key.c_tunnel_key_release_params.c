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
struct tcf_tunnel_key_params {scalar_t__ tcft_action; TYPE_1__* tcft_enc_metadata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 scalar_t__ TCA_TUNNEL_KEY_ACT_SET ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_tunnel_key_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void tunnel_key_release_params(struct tcf_tunnel_key_params *p)
{
	if (!p)
		return;
	if (p->tcft_action == TCA_TUNNEL_KEY_ACT_SET)
		dst_release(&p->tcft_enc_metadata->dst);

	kfree_rcu(p, rcu);
}