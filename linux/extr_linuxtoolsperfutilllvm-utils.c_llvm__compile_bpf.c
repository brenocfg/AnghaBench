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
typedef  int /*<<< orphan*/  serr ;
typedef  int /*<<< orphan*/  nr_cpus_avail_str ;
typedef  int /*<<< orphan*/  linux_version_code_str ;
struct TYPE_2__ {char* clang_opt; char* clang_bpf_cmd_template; char* opts; int /*<<< orphan*/  llc_path; int /*<<< orphan*/  clang_path; } ;

/* Variables and functions */
 char* CLANG_BPF_CMD_DEFAULT_TEMPLATE ; 
 int ENOENT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PERF_INCLUDE_DIR ; 
 int STRERR_BUFSIZE ; 
 scalar_t__ asprintf (char**,char*,char const*,...) ; 
 int errno ; 
 scalar_t__ fetch_kernel_version (unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_set_env (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  llvm__get_kbuild_opts (char**,char**) ; 
 int llvm__get_nr_cpus () ; 
 TYPE_1__ llvm_param ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int read_from_pipe (char const*,void**,size_t*) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 int search_program (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 
 char* system_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version_notice () ; 

int llvm__compile_bpf(const char *path, void **p_obj_buf,
		      size_t *p_obj_buf_sz)
{
	size_t obj_buf_sz;
	void *obj_buf = NULL;
	int err, nr_cpus_avail;
	unsigned int kernel_version;
	char linux_version_code_str[64];
	const char *clang_opt = llvm_param.clang_opt;
	char clang_path[PATH_MAX], llc_path[PATH_MAX], abspath[PATH_MAX], nr_cpus_avail_str[64];
	char serr[STRERR_BUFSIZE];
	char *kbuild_dir = NULL, *kbuild_include_opts = NULL,
	     *perf_bpf_include_opts = NULL;
	const char *template = llvm_param.clang_bpf_cmd_template;
	char *pipe_template = NULL;
	const char *opts = llvm_param.opts;
	char *command_echo = NULL, *command_out;
	char *perf_include_dir = system_path(PERF_INCLUDE_DIR);

	if (path[0] != '-' && realpath(path, abspath) == NULL) {
		err = errno;
		pr_err("ERROR: problems with path %s: %s\n",
		       path, str_error_r(err, serr, sizeof(serr)));
		return -err;
	}

	if (!template)
		template = CLANG_BPF_CMD_DEFAULT_TEMPLATE;

	err = search_program(llvm_param.clang_path,
			     "clang", clang_path);
	if (err) {
		pr_err(
"ERROR:\tunable to find clang.\n"
"Hint:\tTry to install latest clang/llvm to support BPF. Check your $PATH\n"
"     \tand 'clang-path' option in [llvm] section of ~/.perfconfig.\n");
		version_notice();
		return -ENOENT;
	}

	/*
	 * This is an optional work. Even it fail we can continue our
	 * work. Needn't to check error return.
	 */
	llvm__get_kbuild_opts(&kbuild_dir, &kbuild_include_opts);

	nr_cpus_avail = llvm__get_nr_cpus();
	snprintf(nr_cpus_avail_str, sizeof(nr_cpus_avail_str), "%d",
		 nr_cpus_avail);

	if (fetch_kernel_version(&kernel_version, NULL, 0))
		kernel_version = 0;

	snprintf(linux_version_code_str, sizeof(linux_version_code_str),
		 "0x%x", kernel_version);
	if (asprintf(&perf_bpf_include_opts, "-I%s/bpf", perf_include_dir) < 0)
		goto errout;
	force_set_env("NR_CPUS", nr_cpus_avail_str);
	force_set_env("LINUX_VERSION_CODE", linux_version_code_str);
	force_set_env("CLANG_EXEC", clang_path);
	force_set_env("CLANG_OPTIONS", clang_opt);
	force_set_env("KERNEL_INC_OPTIONS", kbuild_include_opts);
	force_set_env("PERF_BPF_INC_OPTIONS", perf_bpf_include_opts);
	force_set_env("WORKING_DIR", kbuild_dir ? : ".");

	if (opts) {
		err = search_program(llvm_param.llc_path, "llc", llc_path);
		if (err) {
			pr_err("ERROR:\tunable to find llc.\n"
			       "Hint:\tTry to install latest clang/llvm to support BPF. Check your $PATH\n"
			       "     \tand 'llc-path' option in [llvm] section of ~/.perfconfig.\n");
			version_notice();
			goto errout;
		}

		if (asprintf(&pipe_template, "%s -emit-llvm | %s -march=bpf %s -filetype=obj -o -",
			      template, llc_path, opts) < 0) {
			pr_err("ERROR:\tnot enough memory to setup command line\n");
			goto errout;
		}

		template = pipe_template;

	}

	/*
	 * Since we may reset clang's working dir, path of source file
	 * should be transferred into absolute path, except we want
	 * stdin to be source file (testing).
	 */
	force_set_env("CLANG_SOURCE",
		      (path[0] == '-') ? path : abspath);

	pr_debug("llvm compiling command template: %s\n", template);

	if (asprintf(&command_echo, "echo -n \"%s\"", template) < 0)
		goto errout;

	err = read_from_pipe(command_echo, (void **) &command_out, NULL);
	if (err)
		goto errout;

	pr_debug("llvm compiling command : %s\n", command_out);

	err = read_from_pipe(template, &obj_buf, &obj_buf_sz);
	if (err) {
		pr_err("ERROR:\tunable to compile %s\n", path);
		pr_err("Hint:\tCheck error message shown above.\n");
		pr_err("Hint:\tYou can also pre-compile it into .o using:\n");
		pr_err("     \t\tclang -target bpf -O2 -c %s\n", path);
		pr_err("     \twith proper -I and -D options.\n");
		goto errout;
	}

	free(command_echo);
	free(command_out);
	free(kbuild_dir);
	free(kbuild_include_opts);
	free(perf_bpf_include_opts);
	free(perf_include_dir);

	if (!p_obj_buf)
		free(obj_buf);
	else
		*p_obj_buf = obj_buf;

	if (p_obj_buf_sz)
		*p_obj_buf_sz = obj_buf_sz;
	return 0;
errout:
	free(command_echo);
	free(kbuild_dir);
	free(kbuild_include_opts);
	free(obj_buf);
	free(perf_bpf_include_opts);
	free(perf_include_dir);
	free(pipe_template);
	if (p_obj_buf)
		*p_obj_buf = NULL;
	if (p_obj_buf_sz)
		*p_obj_buf_sz = 0;
	return err;
}