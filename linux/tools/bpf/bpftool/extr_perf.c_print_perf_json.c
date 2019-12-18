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
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
#define  BPF_FD_TYPE_KPROBE 133 
#define  BPF_FD_TYPE_KRETPROBE 132 
#define  BPF_FD_TYPE_RAW_TRACEPOINT 131 
#define  BPF_FD_TYPE_TRACEPOINT 130 
#define  BPF_FD_TYPE_UPROBE 129 
#define  BPF_FD_TYPE_URETPROBE 128 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_int_field (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  jsonw_lluint_field (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_string_field (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  jsonw_uint_field (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void print_perf_json(int pid, int fd, __u32 prog_id, __u32 fd_type,
			    char *buf, __u64 probe_offset, __u64 probe_addr)
{
	jsonw_start_object(json_wtr);
	jsonw_int_field(json_wtr, "pid", pid);
	jsonw_int_field(json_wtr, "fd", fd);
	jsonw_uint_field(json_wtr, "prog_id", prog_id);
	switch (fd_type) {
	case BPF_FD_TYPE_RAW_TRACEPOINT:
		jsonw_string_field(json_wtr, "fd_type", "raw_tracepoint");
		jsonw_string_field(json_wtr, "tracepoint", buf);
		break;
	case BPF_FD_TYPE_TRACEPOINT:
		jsonw_string_field(json_wtr, "fd_type", "tracepoint");
		jsonw_string_field(json_wtr, "tracepoint", buf);
		break;
	case BPF_FD_TYPE_KPROBE:
		jsonw_string_field(json_wtr, "fd_type", "kprobe");
		if (buf[0] != '\0') {
			jsonw_string_field(json_wtr, "func", buf);
			jsonw_lluint_field(json_wtr, "offset", probe_offset);
		} else {
			jsonw_lluint_field(json_wtr, "addr", probe_addr);
		}
		break;
	case BPF_FD_TYPE_KRETPROBE:
		jsonw_string_field(json_wtr, "fd_type", "kretprobe");
		if (buf[0] != '\0') {
			jsonw_string_field(json_wtr, "func", buf);
			jsonw_lluint_field(json_wtr, "offset", probe_offset);
		} else {
			jsonw_lluint_field(json_wtr, "addr", probe_addr);
		}
		break;
	case BPF_FD_TYPE_UPROBE:
		jsonw_string_field(json_wtr, "fd_type", "uprobe");
		jsonw_string_field(json_wtr, "filename", buf);
		jsonw_lluint_field(json_wtr, "offset", probe_offset);
		break;
	case BPF_FD_TYPE_URETPROBE:
		jsonw_string_field(json_wtr, "fd_type", "uretprobe");
		jsonw_string_field(json_wtr, "filename", buf);
		jsonw_lluint_field(json_wtr, "offset", probe_offset);
		break;
	default:
		break;
	}
	jsonw_end_object(json_wtr);
}