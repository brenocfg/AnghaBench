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
typedef  int /*<<< orphan*/  substring_t ;
struct ramfs_mount_opts {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_mode 128 
 int RAMFS_DEFAULT_MODE ; 
 int S_IALLUGO ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int ramfs_parse_options(char *data, struct ramfs_mount_opts *opts)
{
	substring_t args[MAX_OPT_ARGS];
	int option;
	int token;
	char *p;

	opts->mode = RAMFS_DEFAULT_MODE;

	while ((p = strsep(&data, ",")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_mode:
			if (match_octal(&args[0], &option))
				return -EINVAL;
			opts->mode = option & S_IALLUGO;
			break;
		/*
		 * We might like to report bad mount options here;
		 * but traditionally ramfs has ignored all mount options,
		 * and as it is used as a !CONFIG_SHMEM simple substitute
		 * for tmpfs, better continue to ignore other mount options.
		 */
		}
	}

	return 0;
}