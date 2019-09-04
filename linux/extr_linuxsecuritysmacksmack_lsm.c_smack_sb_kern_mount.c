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
struct super_block {int dummy; } ;
struct security_mnt_opts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  security_free_mnt_opts (struct security_mnt_opts*) ; 
 int /*<<< orphan*/  security_init_mnt_opts (struct security_mnt_opts*) ; 
 int smack_parse_opts_str (char*,struct security_mnt_opts*) ; 
 int smack_set_mnt_opts (struct super_block*,struct security_mnt_opts*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smack_sb_kern_mount(struct super_block *sb, int flags, void *data)
{
	int rc = 0;
	char *options = data;
	struct security_mnt_opts opts;

	security_init_mnt_opts(&opts);

	if (!options)
		goto out;

	rc = smack_parse_opts_str(options, &opts);
	if (rc)
		goto out_err;

out:
	rc = smack_set_mnt_opts(sb, &opts, 0, NULL);

out_err:
	security_free_mnt_opts(&opts);
	return rc;
}