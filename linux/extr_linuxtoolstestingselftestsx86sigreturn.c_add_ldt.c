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
struct user_desc {int /*<<< orphan*/  entry_number; } ;

/* Variables and functions */
 unsigned short LDT3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_modify_ldt ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int,struct user_desc const*,int) ; 

__attribute__((used)) static void add_ldt(const struct user_desc *desc, unsigned short *var,
		    const char *name)
{
	if (syscall(SYS_modify_ldt, 1, desc, sizeof(*desc)) == 0) {
		*var = LDT3(desc->entry_number);
	} else {
		printf("[NOTE]\tFailed to create %s segment\n", name);
		*var = 0;
	}
}