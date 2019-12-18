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
struct netlbl_lsm_secattr {int dummy; } ;
struct netlbl_calipso_ops {int (* opt_getattr ) (unsigned char const*,struct netlbl_lsm_secattr*) ;} ;

/* Variables and functions */
 int ENOMSG ; 
 struct netlbl_calipso_ops* netlbl_calipso_ops_get () ; 
 int stub1 (unsigned char const*,struct netlbl_lsm_secattr*) ; 

int calipso_getattr(const unsigned char *calipso,
		    struct netlbl_lsm_secattr *secattr)
{
	int ret_val = -ENOMSG;
	const struct netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	if (ops)
		ret_val = ops->opt_getattr(calipso, secattr);
	return ret_val;
}