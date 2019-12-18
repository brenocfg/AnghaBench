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
typedef  int __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int bpf_get_current_pid_tgid () ; 
 int* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int bpf_send_signal (int) ; 
 int /*<<< orphan*/  info_map ; 
 int /*<<< orphan*/  status_map ; 

int bpf_send_signal_test(void *ctx)
{
	__u64 *info_val, *status_val;
	__u32 key = 0, pid, sig;
	int ret;

	status_val = bpf_map_lookup_elem(&status_map, &key);
	if (!status_val || *status_val != 0)
		return 0;

	info_val = bpf_map_lookup_elem(&info_map, &key);
	if (!info_val || *info_val == 0)
		return 0;

	sig = *info_val >> 32;
	pid = *info_val & 0xffffFFFF;

	if ((bpf_get_current_pid_tgid() >> 32) == pid) {
		ret = bpf_send_signal(sig);
		if (ret == 0)
			*status_val = 1;
	}

	return 0;
}