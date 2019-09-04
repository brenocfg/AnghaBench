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
struct netlbl_calipso_ops {int (* doi_add ) (struct calipso_doi*,struct netlbl_audit*) ;} ;
struct netlbl_audit {int dummy; } ;
struct calipso_doi {int dummy; } ;

/* Variables and functions */
 int ENOMSG ; 
 struct netlbl_calipso_ops* netlbl_calipso_ops_get () ; 
 int stub1 (struct calipso_doi*,struct netlbl_audit*) ; 

int calipso_doi_add(struct calipso_doi *doi_def,
		    struct netlbl_audit *audit_info)
{
	int ret_val = -ENOMSG;
	const struct netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	if (ops)
		ret_val = ops->doi_add(doi_def, audit_info);
	return ret_val;
}