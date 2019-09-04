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
struct lockdep_map {int dummy; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lockdep_init_map (struct lockdep_map*,char const*,struct lock_class_key*,int) ; 

void lockdep_init_map(struct lockdep_map *lock, const char *name,
		      struct lock_class_key *key, int subclass)
{
	__lockdep_init_map(lock, name, key, subclass);
}