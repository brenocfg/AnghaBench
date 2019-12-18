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
struct kasan_access_info {scalar_t__ access_addr; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 unsigned long TASK_SIZE ; 

__attribute__((used)) static const char *get_wild_bug_type(struct kasan_access_info *info)
{
	const char *bug_type = "unknown-crash";

	if ((unsigned long)info->access_addr < PAGE_SIZE)
		bug_type = "null-ptr-deref";
	else if ((unsigned long)info->access_addr < TASK_SIZE)
		bug_type = "user-memory-access";
	else
		bug_type = "wild-memory-access";

	return bug_type;
}