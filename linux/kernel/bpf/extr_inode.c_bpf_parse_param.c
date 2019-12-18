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
struct fs_parse_result {int uint_32; } ;
struct fs_parameter {int dummy; } ;
struct fs_context {struct bpf_mount_opts* fs_private; } ;
struct bpf_mount_opts {int mode; } ;

/* Variables and functions */
 int ENOPARAM ; 
#define  OPT_MODE 128 
 int S_IALLUGO ; 
 int /*<<< orphan*/  bpf_fs_parameters ; 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 

__attribute__((used)) static int bpf_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct bpf_mount_opts *opts = fc->fs_private;
	struct fs_parse_result result;
	int opt;

	opt = fs_parse(fc, &bpf_fs_parameters, param, &result);
	if (opt < 0)
		/* We might like to report bad mount options here, but
		 * traditionally we've ignored all mount options, so we'd
		 * better continue to ignore non-existing options for bpf.
		 */
		return opt == -ENOPARAM ? 0 : opt;

	switch (opt) {
	case OPT_MODE:
		opts->mode = result.uint_32 & S_IALLUGO;
		break;
	}

	return 0;
}