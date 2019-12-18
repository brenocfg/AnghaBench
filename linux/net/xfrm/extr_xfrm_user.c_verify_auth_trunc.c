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
struct xfrm_algo_auth {char* alg_name; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t XFRMA_ALG_AUTH_TRUNC ; 
 struct xfrm_algo_auth* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 scalar_t__ xfrm_alg_auth_len (struct xfrm_algo_auth*) ; 

__attribute__((used)) static int verify_auth_trunc(struct nlattr **attrs)
{
	struct nlattr *rt = attrs[XFRMA_ALG_AUTH_TRUNC];
	struct xfrm_algo_auth *algp;

	if (!rt)
		return 0;

	algp = nla_data(rt);
	if (nla_len(rt) < (int)xfrm_alg_auth_len(algp))
		return -EINVAL;

	algp->alg_name[sizeof(algp->alg_name) - 1] = '\0';
	return 0;
}