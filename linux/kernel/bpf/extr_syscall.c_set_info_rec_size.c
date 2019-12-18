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
struct bpf_prog_info {int func_info_rec_size; int line_info_rec_size; int jited_line_info_rec_size; scalar_t__ nr_jited_line_info; scalar_t__ nr_line_info; scalar_t__ nr_func_info; } ;
struct bpf_line_info {int dummy; } ;
struct bpf_func_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int set_info_rec_size(struct bpf_prog_info *info)
{
	/*
	 * Ensure info.*_rec_size is the same as kernel expected size
	 *
	 * or
	 *
	 * Only allow zero *_rec_size if both _rec_size and _cnt are
	 * zero.  In this case, the kernel will set the expected
	 * _rec_size back to the info.
	 */

	if ((info->nr_func_info || info->func_info_rec_size) &&
	    info->func_info_rec_size != sizeof(struct bpf_func_info))
		return -EINVAL;

	if ((info->nr_line_info || info->line_info_rec_size) &&
	    info->line_info_rec_size != sizeof(struct bpf_line_info))
		return -EINVAL;

	if ((info->nr_jited_line_info || info->jited_line_info_rec_size) &&
	    info->jited_line_info_rec_size != sizeof(__u64))
		return -EINVAL;

	info->func_info_rec_size = sizeof(struct bpf_func_info);
	info->line_info_rec_size = sizeof(struct bpf_line_info);
	info->jited_line_info_rec_size = sizeof(__u64);

	return 0;
}