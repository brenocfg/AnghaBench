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
struct sock {int dummy; } ;
struct netlbl_lsm_secattr {int dummy; } ;
struct netlbl_calipso_ops {int (* sock_setattr ) (struct sock*,struct calipso_doi const*,struct netlbl_lsm_secattr const*) ;} ;
struct calipso_doi {int dummy; } ;

/* Variables and functions */
 int ENOMSG ; 
 struct netlbl_calipso_ops* netlbl_calipso_ops_get () ; 
 int stub1 (struct sock*,struct calipso_doi const*,struct netlbl_lsm_secattr const*) ; 

int calipso_sock_setattr(struct sock *sk,
			 const struct calipso_doi *doi_def,
			 const struct netlbl_lsm_secattr *secattr)
{
	int ret_val = -ENOMSG;
	const struct netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	if (ops)
		ret_val = ops->sock_setattr(sk, doi_def, secattr);
	return ret_val;
}