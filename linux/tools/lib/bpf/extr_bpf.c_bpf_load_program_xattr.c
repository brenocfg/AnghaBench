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
union bpf_attr {int insn_cnt; int log_level; size_t log_size; scalar_t__ func_info_rec_size; scalar_t__ line_info_rec_size; void* log_buf; void* line_info; scalar_t__ line_info_cnt; void* func_info; scalar_t__ func_info_cnt; int /*<<< orphan*/  prog_flags; int /*<<< orphan*/  prog_name; int /*<<< orphan*/  prog_btf_fd; int /*<<< orphan*/  prog_ifindex; int /*<<< orphan*/  kern_version; void* license; void* insns; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
struct bpf_load_program_attr {int log_level; char* insns; char* license; scalar_t__ func_info_rec_size; char* func_info; scalar_t__ line_info_rec_size; char* line_info; scalar_t__ line_info_cnt; scalar_t__ func_info_cnt; int /*<<< orphan*/  prog_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  prog_btf_fd; int /*<<< orphan*/  prog_ifindex; int /*<<< orphan*/  kern_version; scalar_t__ insns_cnt; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ BPF_OBJ_NAME_LEN ; 
 scalar_t__ E2BIG ; 
 int EINVAL ; 
 void* alloc_zero_tailing_info (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 void* ptr_to_u64 (char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int sys_bpf_prog_load (union bpf_attr*,int) ; 

int bpf_load_program_xattr(const struct bpf_load_program_attr *load_attr,
			   char *log_buf, size_t log_buf_sz)
{
	void *finfo = NULL, *linfo = NULL;
	union bpf_attr attr;
	__u32 log_level;
	int fd;

	if (!load_attr || !log_buf != !log_buf_sz)
		return -EINVAL;

	log_level = load_attr->log_level;
	if (log_level > (4 | 2 | 1) || (log_level && !log_buf))
		return -EINVAL;

	memset(&attr, 0, sizeof(attr));
	attr.prog_type = load_attr->prog_type;
	attr.expected_attach_type = load_attr->expected_attach_type;
	attr.insn_cnt = (__u32)load_attr->insns_cnt;
	attr.insns = ptr_to_u64(load_attr->insns);
	attr.license = ptr_to_u64(load_attr->license);

	attr.log_level = log_level;
	if (log_level) {
		attr.log_buf = ptr_to_u64(log_buf);
		attr.log_size = log_buf_sz;
	} else {
		attr.log_buf = ptr_to_u64(NULL);
		attr.log_size = 0;
	}

	attr.kern_version = load_attr->kern_version;
	attr.prog_ifindex = load_attr->prog_ifindex;
	attr.prog_btf_fd = load_attr->prog_btf_fd;
	attr.func_info_rec_size = load_attr->func_info_rec_size;
	attr.func_info_cnt = load_attr->func_info_cnt;
	attr.func_info = ptr_to_u64(load_attr->func_info);
	attr.line_info_rec_size = load_attr->line_info_rec_size;
	attr.line_info_cnt = load_attr->line_info_cnt;
	attr.line_info = ptr_to_u64(load_attr->line_info);
	if (load_attr->name)
		memcpy(attr.prog_name, load_attr->name,
		       min(strlen(load_attr->name), BPF_OBJ_NAME_LEN - 1));
	attr.prog_flags = load_attr->prog_flags;

	fd = sys_bpf_prog_load(&attr, sizeof(attr));
	if (fd >= 0)
		return fd;

	/* After bpf_prog_load, the kernel may modify certain attributes
	 * to give user space a hint how to deal with loading failure.
	 * Check to see whether we can make some changes and load again.
	 */
	while (errno == E2BIG && (!finfo || !linfo)) {
		if (!finfo && attr.func_info_cnt &&
		    attr.func_info_rec_size < load_attr->func_info_rec_size) {
			/* try with corrected func info records */
			finfo = alloc_zero_tailing_info(load_attr->func_info,
							load_attr->func_info_cnt,
							load_attr->func_info_rec_size,
							attr.func_info_rec_size);
			if (!finfo)
				goto done;

			attr.func_info = ptr_to_u64(finfo);
			attr.func_info_rec_size = load_attr->func_info_rec_size;
		} else if (!linfo && attr.line_info_cnt &&
			   attr.line_info_rec_size <
			   load_attr->line_info_rec_size) {
			linfo = alloc_zero_tailing_info(load_attr->line_info,
							load_attr->line_info_cnt,
							load_attr->line_info_rec_size,
							attr.line_info_rec_size);
			if (!linfo)
				goto done;

			attr.line_info = ptr_to_u64(linfo);
			attr.line_info_rec_size = load_attr->line_info_rec_size;
		} else {
			break;
		}

		fd = sys_bpf_prog_load(&attr, sizeof(attr));

		if (fd >= 0)
			goto done;
	}

	if (log_level || !log_buf)
		goto done;

	/* Try again with log */
	attr.log_buf = ptr_to_u64(log_buf);
	attr.log_size = log_buf_sz;
	attr.log_level = 1;
	log_buf[0] = 0;
	fd = sys_bpf_prog_load(&attr, sizeof(attr));
done:
	free(finfo);
	free(linfo);
	return fd;
}