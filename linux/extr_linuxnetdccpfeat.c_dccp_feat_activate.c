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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
typedef  int /*<<< orphan*/  dccp_feat_val ;

/* Variables and functions */
 int __dccp_feat_activate (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dccp_feat_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_feat_activate(struct sock *sk, u8 feat_num, bool local,
			      dccp_feat_val const *fval)
{
	return __dccp_feat_activate(sk, dccp_feat_index(feat_num), local, fval);
}