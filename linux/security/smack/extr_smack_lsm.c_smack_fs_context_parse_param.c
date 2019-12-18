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
struct fs_parse_result {int dummy; } ;
struct fs_parameter {int /*<<< orphan*/ * string; } ;
struct fs_context {int /*<<< orphan*/  security; } ;

/* Variables and functions */
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 
 int smack_add_opt (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smack_fs_parameters ; 

__attribute__((used)) static int smack_fs_context_parse_param(struct fs_context *fc,
					struct fs_parameter *param)
{
	struct fs_parse_result result;
	int opt, rc;

	opt = fs_parse(fc, &smack_fs_parameters, param, &result);
	if (opt < 0)
		return opt;

	rc = smack_add_opt(opt, param->string, &fc->security);
	if (!rc)
		param->string = NULL;
	return rc;
}