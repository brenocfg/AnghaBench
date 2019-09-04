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
struct bpf_prog_info {char* id; char const* name; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 int bpf_prog_get_fd_by_id (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_string_field (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  jsonw_uint_field (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char const*,char const*,char const*) ; 

__attribute__((used)) static int show_bpf_prog(int id, const char *attach_type_str,
			 const char *attach_flags_str,
			 int level)
{
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);
	int prog_fd;

	prog_fd = bpf_prog_get_fd_by_id(id);
	if (prog_fd < 0)
		return -1;

	if (bpf_obj_get_info_by_fd(prog_fd, &info, &info_len)) {
		close(prog_fd);
		return -1;
	}

	if (json_output) {
		jsonw_start_object(json_wtr);
		jsonw_uint_field(json_wtr, "id", info.id);
		jsonw_string_field(json_wtr, "attach_type",
				   attach_type_str);
		jsonw_string_field(json_wtr, "attach_flags",
				   attach_flags_str);
		jsonw_string_field(json_wtr, "name", info.name);
		jsonw_end_object(json_wtr);
	} else {
		printf("%s%-8u %-15s %-15s %-15s\n", level ? "    " : "",
		       info.id,
		       attach_type_str,
		       attach_flags_str,
		       info.name);
	}

	close(prog_fd);
	return 0;
}