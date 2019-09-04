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
struct mutex {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_inlist_lock_noload (struct list_head*,char const*,int*,struct mutex*) ; 
 void* try_then_request_module (int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static void *
find_inlist_lock(struct list_head *head, const char *name, const char *prefix,
		 int *error, struct mutex *mutex)
{
	return try_then_request_module(
			find_inlist_lock_noload(head, name, error, mutex),
			"%s%s", prefix, name);
}