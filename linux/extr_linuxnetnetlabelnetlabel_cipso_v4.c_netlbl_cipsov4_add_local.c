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
struct netlbl_audit {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct cipso_v4_doi {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPSO_V4_MAP_LOCAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NLBL_CIPSOV4_A_TAGLST ; 
 int cipso_v4_doi_add (struct cipso_v4_doi*,struct netlbl_audit*) ; 
 int /*<<< orphan*/  cipso_v4_doi_free (struct cipso_v4_doi*) ; 
 struct cipso_v4_doi* kmalloc (int,int /*<<< orphan*/ ) ; 
 int netlbl_cipsov4_add_common (struct genl_info*,struct cipso_v4_doi*) ; 

__attribute__((used)) static int netlbl_cipsov4_add_local(struct genl_info *info,
				    struct netlbl_audit *audit_info)
{
	int ret_val;
	struct cipso_v4_doi *doi_def = NULL;

	if (!info->attrs[NLBL_CIPSOV4_A_TAGLST])
		return -EINVAL;

	doi_def = kmalloc(sizeof(*doi_def), GFP_KERNEL);
	if (doi_def == NULL)
		return -ENOMEM;
	doi_def->type = CIPSO_V4_MAP_LOCAL;

	ret_val = netlbl_cipsov4_add_common(info, doi_def);
	if (ret_val != 0)
		goto add_local_failure;

	ret_val = cipso_v4_doi_add(doi_def, audit_info);
	if (ret_val != 0)
		goto add_local_failure;
	return 0;

add_local_failure:
	cipso_v4_doi_free(doi_def);
	return ret_val;
}