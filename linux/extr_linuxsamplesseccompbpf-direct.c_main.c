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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  __NR_read ; 
 int /*<<< orphan*/  __NR_write ; 
 scalar_t__ install_emulator () ; 
 scalar_t__ install_filter () ; 
 int /*<<< orphan*/  payload (char*) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

int main(int argc, char **argv)
{
	char buf[4096];
	ssize_t bytes = 0;
	if (install_emulator())
		return 1;
	if (install_filter())
		return 1;
	syscall(__NR_write, STDOUT_FILENO,
		payload("OHAI! WHAT IS YOUR NAME? "));
	bytes = syscall(__NR_read, STDIN_FILENO, buf, sizeof(buf));
	syscall(__NR_write, STDOUT_FILENO, payload("HELLO, "));
	syscall(__NR_write, STDOUT_FILENO, buf, bytes);
	syscall(__NR_write, STDERR_FILENO,
		payload("Error message going to STDERR\n"));
	return 0;
}