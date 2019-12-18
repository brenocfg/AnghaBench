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
struct user_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ safe_modify_ldt (int,struct user_desc*,int) ; 

__attribute__((used)) static void fail_install(struct user_desc *desc)
{
	if (safe_modify_ldt(0x11, desc, sizeof(*desc)) == 0) {
		printf("[FAIL]\tmodify_ldt accepted a bad descriptor\n");
		nerrs++;
	} else if (errno == ENOSYS) {
		printf("[OK]\tmodify_ldt returned -ENOSYS\n");
	} else {
		printf("[OK]\tmodify_ldt failure %d\n", errno);
	}
}