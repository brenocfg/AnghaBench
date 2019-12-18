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
struct bpf_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_FLOW_DISSECTOR ; 
 int bpf_flow_load (struct bpf_object**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int bpf_object__pin (struct bpf_object*,char*) ; 
 int bpf_prog_attach (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_map_name ; 
 char* cfg_path_name ; 
 char* cfg_pin_path ; 
 int /*<<< orphan*/  cfg_section_name ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void load_and_attach_program(void)
{
	int prog_fd, ret;
	struct bpf_object *obj;

	ret = bpf_flow_load(&obj, cfg_path_name, cfg_section_name,
			    cfg_map_name, NULL, &prog_fd, NULL);
	if (ret)
		error(1, 0, "bpf_flow_load %s", cfg_path_name);

	ret = bpf_prog_attach(prog_fd, 0 /* Ignore */, BPF_FLOW_DISSECTOR, 0);
	if (ret)
		error(1, 0, "bpf_prog_attach %s", cfg_path_name);

	ret = bpf_object__pin(obj, cfg_pin_path);
	if (ret)
		error(1, 0, "bpf_object__pin %s", cfg_pin_path);
}