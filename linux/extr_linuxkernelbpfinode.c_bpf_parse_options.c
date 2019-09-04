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
struct bpf_mount_opts {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
#define  OPT_MODE 128 
 int S_IALLUGO ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  bpf_mount_tokens ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int bpf_parse_options(char *data, struct bpf_mount_opts *opts)
{
	substring_t args[MAX_OPT_ARGS];
	int option, token;
	char *ptr;

	opts->mode = S_IRWXUGO;

	while ((ptr = strsep(&data, ",")) != NULL) {
		if (!*ptr)
			continue;

		token = match_token(ptr, bpf_mount_tokens, args);
		switch (token) {
		case OPT_MODE:
			if (match_octal(&args[0], &option))
				return -EINVAL;
			opts->mode = option & S_IALLUGO;
			break;
		/* We might like to report bad mount options here, but
		 * traditionally we've ignored all mount options, so we'd
		 * better continue to ignore non-existing options for bpf.
		 */
		}
	}

	return 0;
}