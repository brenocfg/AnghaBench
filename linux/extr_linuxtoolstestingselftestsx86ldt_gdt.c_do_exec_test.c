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
struct user_desc {int limit; int seg_32bit; int contents; int /*<<< orphan*/  useable; int /*<<< orphan*/  seg_not_present; int /*<<< orphan*/  limit_in_pages; int /*<<< orphan*/  read_exec_only; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  entry_number; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int AR_DB ; 
 int AR_DPL3 ; 
 int AR_P ; 
 int AR_S ; 
 int AR_TYPE_XRCODE ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  execl (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  install_valid (struct user_desc*,int) ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_exec_test(void)
{
	printf("[RUN]\tTest exec\n");

	struct user_desc desc = {
		.entry_number    = 0,
		.base_addr       = 0,
		.limit           = 42,
		.seg_32bit       = 1,
		.contents        = 2, /* Code, not conforming */
		.read_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 0,
		.useable         = 0
	};
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE | AR_S | AR_P | AR_DB);

	pid_t child = fork();
	if (child == 0) {
		execl("/proc/self/exe", "ldt_gdt_test_exec", NULL);
		printf("[FAIL]\tCould not exec self\n");
		exit(1);	/* exec failed */
	} else {
		int status;
		if (waitpid(child, &status, 0) != child ||
		    !WIFEXITED(status)) {
			printf("[FAIL]\tChild died\n");
			nerrs++;
		} else if (WEXITSTATUS(status) != 0) {
			printf("[FAIL]\tChild failed\n");
			nerrs++;
		} else {
			printf("[OK]\tChild succeeded\n");
		}
	}
}