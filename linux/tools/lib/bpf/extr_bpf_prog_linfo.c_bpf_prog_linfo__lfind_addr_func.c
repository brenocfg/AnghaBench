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
struct bpf_prog_linfo {size_t nr_jited_func; size_t* nr_jited_linfo_per_func; size_t* jited_linfo_func_idx; size_t jited_rec_size; void* raw_jited_linfo; size_t rec_size; void* raw_linfo; } ;
typedef  void bpf_line_info ;
typedef  scalar_t__ const __u64 ;
typedef  size_t __u32 ;

/* Variables and functions */

const struct bpf_line_info *
bpf_prog_linfo__lfind_addr_func(const struct bpf_prog_linfo *prog_linfo,
				__u64 addr, __u32 func_idx, __u32 nr_skip)
{
	__u32 jited_rec_size, rec_size, nr_linfo, start, i;
	const void *raw_jited_linfo, *raw_linfo;
	const __u64 *jited_linfo;

	if (func_idx >= prog_linfo->nr_jited_func)
		return NULL;

	nr_linfo = prog_linfo->nr_jited_linfo_per_func[func_idx];
	if (nr_skip >= nr_linfo)
		return NULL;

	start = prog_linfo->jited_linfo_func_idx[func_idx] + nr_skip;
	jited_rec_size = prog_linfo->jited_rec_size;
	raw_jited_linfo = prog_linfo->raw_jited_linfo +
		(start * jited_rec_size);
	jited_linfo = raw_jited_linfo;
	if (addr < *jited_linfo)
		return NULL;

	nr_linfo -= nr_skip;
	rec_size = prog_linfo->rec_size;
	raw_linfo = prog_linfo->raw_linfo + (start * rec_size);
	for (i = 0; i < nr_linfo; i++) {
		if (addr < *jited_linfo)
			break;

		raw_linfo += rec_size;
		raw_jited_linfo += jited_rec_size;
		jited_linfo = raw_jited_linfo;
	}

	return raw_linfo - rec_size;
}