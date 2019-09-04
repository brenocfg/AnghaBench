#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lock_class_key {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dep_map; } ;
typedef  TYPE_1__ liblockdep_pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_init_map (int /*<<< orphan*/ *,char const*,struct lock_class_key*,int /*<<< orphan*/ ) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int __mutex_init(liblockdep_pthread_mutex_t *lock,
				const char *name,
				struct lock_class_key *key,
				const pthread_mutexattr_t *__mutexattr)
{
	lockdep_init_map(&lock->dep_map, name, key, 0);
	return pthread_mutex_init(&lock->mutex, __mutexattr);
}