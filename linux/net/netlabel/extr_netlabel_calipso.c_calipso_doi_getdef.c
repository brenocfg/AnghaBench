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
typedef  int /*<<< orphan*/  u32 ;
struct netlbl_calipso_ops {struct calipso_doi* (* doi_getdef ) (int /*<<< orphan*/ ) ;} ;
struct calipso_doi {int dummy; } ;

/* Variables and functions */
 struct netlbl_calipso_ops* netlbl_calipso_ops_get () ; 
 struct calipso_doi* stub1 (int /*<<< orphan*/ ) ; 

struct calipso_doi *calipso_doi_getdef(u32 doi)
{
	struct calipso_doi *ret_val = NULL;
	const struct netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	if (ops)
		ret_val = ops->doi_getdef(doi);
	return ret_val;
}