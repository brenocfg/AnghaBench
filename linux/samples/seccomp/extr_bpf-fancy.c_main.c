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
struct sock_fprog {unsigned short len; struct sock_filter* filter; } ;
struct sock_filter {int dummy; } ;
struct bpf_labels {int /*<<< orphan*/  count; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  msg2 ;
typedef  int /*<<< orphan*/  msg1 ;
typedef  int /*<<< orphan*/  filter ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct sock_filter ALLOW ; 
 struct sock_filter ARG (int) ; 
 struct sock_filter DENY ; 
 struct sock_filter JEQ (unsigned long,struct sock_filter) ; 
 struct sock_filter JGE (int,struct sock_filter) ; 
 struct sock_filter JLT (int,struct sock_filter) ; 
 struct sock_filter JNE (unsigned long,struct sock_filter) ; 
 struct sock_filter JUMP (struct bpf_labels*,int /*<<< orphan*/ ) ; 
 struct sock_filter LABEL (struct bpf_labels*,int /*<<< orphan*/ ) ; 
 struct sock_filter LOAD_SYSCALL_NR ; 
 int /*<<< orphan*/  PR_SET_NO_NEW_PRIVS ; 
 int /*<<< orphan*/  PR_SET_SECCOMP ; 
 int /*<<< orphan*/  SECCOMP_MODE_FILTER ; 
 unsigned long STDERR_FILENO ; 
 unsigned long STDIN_FILENO ; 
 unsigned long STDOUT_FILENO ; 
 struct sock_filter SYSCALL (int /*<<< orphan*/ ,struct sock_filter) ; 
 int /*<<< orphan*/  __NR_exit ; 
 int /*<<< orphan*/  __NR_exit_group ; 
 int /*<<< orphan*/  __NR_read ; 
 int /*<<< orphan*/  __NR_write ; 
 int /*<<< orphan*/  bpf_resolve_jumps (struct bpf_labels*,struct sock_filter*,int) ; 
 int /*<<< orphan*/  buf_len ; 
 int /*<<< orphan*/  msg1_len ; 
 int /*<<< orphan*/  msg2_len ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int,struct sock_fprog*,...) ; 
 int /*<<< orphan*/  read ; 
 int strlen (char const*) ; 
 int syscall (int /*<<< orphan*/ ,unsigned long,char const*,int) ; 
 int /*<<< orphan*/  write_buf ; 
 int /*<<< orphan*/  write_fd ; 

int main(int argc, char **argv)
{
	struct bpf_labels l = {
		.count = 0,
	};
	static const char msg1[] = "Please type something: ";
	static const char msg2[] = "You typed: ";
	char buf[256];
	struct sock_filter filter[] = {
		/* TODO: LOAD_SYSCALL_NR(arch) and enforce an arch */
		LOAD_SYSCALL_NR,
		SYSCALL(__NR_exit, ALLOW),
		SYSCALL(__NR_exit_group, ALLOW),
		SYSCALL(__NR_write, JUMP(&l, write_fd)),
		SYSCALL(__NR_read, JUMP(&l, read)),
		DENY,  /* Don't passthrough into a label */

		LABEL(&l, read),
		ARG(0),
		JNE(STDIN_FILENO, DENY),
		ARG(1),
		JNE((unsigned long)buf, DENY),
		ARG(2),
		JGE(sizeof(buf), DENY),
		ALLOW,

		LABEL(&l, write_fd),
		ARG(0),
		JEQ(STDOUT_FILENO, JUMP(&l, write_buf)),
		JEQ(STDERR_FILENO, JUMP(&l, write_buf)),
		DENY,

		LABEL(&l, write_buf),
		ARG(1),
		JEQ((unsigned long)msg1, JUMP(&l, msg1_len)),
		JEQ((unsigned long)msg2, JUMP(&l, msg2_len)),
		JEQ((unsigned long)buf, JUMP(&l, buf_len)),
		DENY,

		LABEL(&l, msg1_len),
		ARG(2),
		JLT(sizeof(msg1), ALLOW),
		DENY,

		LABEL(&l, msg2_len),
		ARG(2),
		JLT(sizeof(msg2), ALLOW),
		DENY,

		LABEL(&l, buf_len),
		ARG(2),
		JLT(sizeof(buf), ALLOW),
		DENY,
	};
	struct sock_fprog prog = {
		.filter = filter,
		.len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
	};
	ssize_t bytes;
	bpf_resolve_jumps(&l, filter, sizeof(filter)/sizeof(*filter));

	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
		perror("prctl(NO_NEW_PRIVS)");
		return 1;
	}

	if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) {
		perror("prctl(SECCOMP)");
		return 1;
	}
	syscall(__NR_write, STDOUT_FILENO, msg1, strlen(msg1));
	bytes = syscall(__NR_read, STDIN_FILENO, buf, sizeof(buf)-1);
	bytes = (bytes > 0 ? bytes : 0);
	syscall(__NR_write, STDERR_FILENO, msg2, strlen(msg2));
	syscall(__NR_write, STDERR_FILENO, buf, bytes);
	/* Now get killed */
	syscall(__NR_write, STDERR_FILENO, msg2, strlen(msg2)+2);
	return 0;
}