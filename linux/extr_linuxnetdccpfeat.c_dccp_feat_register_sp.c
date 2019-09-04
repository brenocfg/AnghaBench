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
typedef  int /*<<< orphan*/  u8 ;
struct sock {scalar_t__ sk_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccps_featneg; } ;

/* Variables and functions */
 scalar_t__ DCCP_CLOSED ; 
 int EINVAL ; 
 int EISCONN ; 
 scalar_t__ FEAT_SP ; 
 int __feat_register_sp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_feat_type (int /*<<< orphan*/ ) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 

int dccp_feat_register_sp(struct sock *sk, u8 feat, u8 is_local,
			  u8 const *list, u8 len)
{	 /* any changes must be registered before establishing the connection */
	if (sk->sk_state != DCCP_CLOSED)
		return -EISCONN;
	if (dccp_feat_type(feat) != FEAT_SP)
		return -EINVAL;
	return __feat_register_sp(&dccp_sk(sk)->dccps_featneg, feat, is_local,
				  0, list, len);
}