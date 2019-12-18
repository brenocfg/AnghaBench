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
struct bpf_cgroup_dev_ctx {int access_type; int major; int /*<<< orphan*/  minor; } ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 short BPF_DEVCG_ACC_MKNOD ; 
 short BPF_DEVCG_ACC_READ ; 
 short BPF_DEVCG_ACC_WRITE ; 
#define  BPF_DEVCG_DEV_BLOCK 129 
#define  BPF_DEVCG_DEV_CHAR 128 
 int /*<<< orphan*/  bpf_trace_printk (char*,int,int,int /*<<< orphan*/ ) ; 

int bpf_prog1(struct bpf_cgroup_dev_ctx *ctx)
{
	short type = ctx->access_type & 0xFFFF;
#ifdef DEBUG
	short access = ctx->access_type >> 16;
	char fmt[] = "  %d:%d    \n";

	switch (type) {
	case BPF_DEVCG_DEV_BLOCK:
		fmt[0] = 'b';
		break;
	case BPF_DEVCG_DEV_CHAR:
		fmt[0] = 'c';
		break;
	default:
		fmt[0] = '?';
		break;
	}

	if (access & BPF_DEVCG_ACC_READ)
		fmt[8] = 'r';

	if (access & BPF_DEVCG_ACC_WRITE)
		fmt[9] = 'w';

	if (access & BPF_DEVCG_ACC_MKNOD)
		fmt[10] = 'm';

	bpf_trace_printk(fmt, sizeof(fmt), ctx->major, ctx->minor);
#endif

	/* Allow access to /dev/zero and /dev/random.
	 * Forbid everything else.
	 */
	if (ctx->major != 1 || type != BPF_DEVCG_DEV_CHAR)
		return 0;

	switch (ctx->minor) {
	case 5: /* 1:5 /dev/zero */
	case 9: /* 1:9 /dev/urandom */
		return 1;
	}

	return 0;
}