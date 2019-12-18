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
struct bpf_attach_info {int flow_dissector_id; } ;
typedef  int __u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BPF_FLOW_DISSECTOR ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int bpf_prog_query (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int query_flow_dissector(struct bpf_attach_info *attach_info)
{
	__u32 attach_flags;
	__u32 prog_ids[1];
	__u32 prog_cnt;
	int err;
	int fd;

	fd = open("/proc/self/ns/net", O_RDONLY);
	if (fd < 0) {
		p_err("can't open /proc/self/ns/net: %s",
		      strerror(errno));
		return -1;
	}
	prog_cnt = ARRAY_SIZE(prog_ids);
	err = bpf_prog_query(fd, BPF_FLOW_DISSECTOR, 0,
			     &attach_flags, prog_ids, &prog_cnt);
	close(fd);
	if (err) {
		if (errno == EINVAL) {
			/* Older kernel's don't support querying
			 * flow dissector programs.
			 */
			errno = 0;
			return 0;
		}
		p_err("can't query prog: %s", strerror(errno));
		return -1;
	}

	if (prog_cnt == 1)
		attach_info->flow_dissector_id = prog_ids[0];

	return 0;
}