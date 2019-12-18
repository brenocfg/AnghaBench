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
struct netlbl_calipso_ops {int /*<<< orphan*/  (* doi_free ) (struct calipso_doi*) ;} ;
struct calipso_doi {int dummy; } ;

/* Variables and functions */
 struct netlbl_calipso_ops* netlbl_calipso_ops_get () ; 
 int /*<<< orphan*/  stub1 (struct calipso_doi*) ; 

void calipso_doi_free(struct calipso_doi *doi_def)
{
	const struct netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	if (ops)
		ops->doi_free(doi_def);
}