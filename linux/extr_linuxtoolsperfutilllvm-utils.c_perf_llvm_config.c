#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dump_obj; int user_set_param; void* opts; void* kbuild_opts; void* kbuild_dir; void* clang_opt; void* clang_bpf_cmd_template; void* clang_path; } ;

/* Variables and functions */
 TYPE_1__ llvm_param ; 
 int /*<<< orphan*/  perf_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strstarts (char const*,char*) ; 

int perf_llvm_config(const char *var, const char *value)
{
	if (!strstarts(var, "llvm."))
		return 0;
	var += sizeof("llvm.") - 1;

	if (!strcmp(var, "clang-path"))
		llvm_param.clang_path = strdup(value);
	else if (!strcmp(var, "clang-bpf-cmd-template"))
		llvm_param.clang_bpf_cmd_template = strdup(value);
	else if (!strcmp(var, "clang-opt"))
		llvm_param.clang_opt = strdup(value);
	else if (!strcmp(var, "kbuild-dir"))
		llvm_param.kbuild_dir = strdup(value);
	else if (!strcmp(var, "kbuild-opts"))
		llvm_param.kbuild_opts = strdup(value);
	else if (!strcmp(var, "dump-obj"))
		llvm_param.dump_obj = !!perf_config_bool(var, value);
	else if (!strcmp(var, "opts"))
		llvm_param.opts = strdup(value);
	else {
		pr_debug("Invalid LLVM config option: %s\n", value);
		return -1;
	}
	llvm_param.user_set_param = true;
	return 0;
}