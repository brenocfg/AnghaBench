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

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void
version_notice(void)
{
	pr_err(
"     \tLLVM 3.7 or newer is required. Which can be found from http://llvm.org\n"
"     \tYou may want to try git trunk:\n"
"     \t\tgit clone http://llvm.org/git/llvm.git\n"
"     \t\t     and\n"
"     \t\tgit clone http://llvm.org/git/clang.git\n\n"
"     \tOr fetch the latest clang/llvm 3.7 from pre-built llvm packages for\n"
"     \tdebian/ubuntu:\n"
"     \t\thttp://llvm.org/apt\n\n"
"     \tIf you are using old version of clang, change 'clang-bpf-cmd-template'\n"
"     \toption in [llvm] section of ~/.perfconfig to:\n\n"
"     \t  \"$CLANG_EXEC $CLANG_OPTIONS $KERNEL_INC_OPTIONS $PERF_BPF_INC_OPTIONS \\\n"
"     \t     -working-directory $WORKING_DIR -c $CLANG_SOURCE \\\n"
"     \t     -emit-llvm -o - | /path/to/llc -march=bpf -filetype=obj -o -\"\n"
"     \t(Replace /path/to/llc with path to your llc)\n\n"
);
}