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
struct sem_t_ {int dummy; } ;
struct sched_param {int dummy; } ;
struct ptw32_mcs_node_t_ {int dummy; } ;
struct ptw32_cleanup_t {int dummy; } ;
struct pthread_spinlock_t_ {int dummy; } ;
struct pthread_rwlockattr_t_ {int dummy; } ;
struct pthread_rwlock_t_ {int dummy; } ;
struct pthread_once_t_ {int dummy; } ;
struct pthread_mutexattr_t_ {int dummy; } ;
struct pthread_mutex_t_ {int dummy; } ;
struct pthread_key_t_ {int dummy; } ;
struct pthread_condattr_t_ {int dummy; } ;
struct pthread_cond_t_ {int dummy; } ;
struct pthread_barrierattr_t_ {int dummy; } ;
struct pthread_barrier_t_ {int dummy; } ;
struct pthread_attr_t_ {int dummy; } ;
typedef  int /*<<< orphan*/  ptw32_thread_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

int
main()
{
  printf("Sizes of pthreads-win32 structs\n");
  printf("-------------------------------\n");
  printf("%30s %4d\n", "pthread_t", (int)sizeof(pthread_t));
  printf("%30s %4d\n", "ptw32_thread_t", (int)sizeof(ptw32_thread_t));
  printf("%30s %4d\n", "pthread_attr_t_", (int)sizeof(struct pthread_attr_t_));
  printf("%30s %4d\n", "sem_t_", (int)sizeof(struct sem_t_));
  printf("%30s %4d\n", "pthread_mutex_t_", (int)sizeof(struct pthread_mutex_t_));
  printf("%30s %4d\n", "pthread_mutexattr_t_", (int)sizeof(struct pthread_mutexattr_t_));
  printf("%30s %4d\n", "pthread_spinlock_t_", (int)sizeof(struct pthread_spinlock_t_));
  printf("%30s %4d\n", "pthread_barrier_t_", (int)sizeof(struct pthread_barrier_t_));
  printf("%30s %4d\n", "pthread_barrierattr_t_", (int)sizeof(struct pthread_barrierattr_t_));
  printf("%30s %4d\n", "pthread_key_t_", (int)sizeof(struct pthread_key_t_));
  printf("%30s %4d\n", "pthread_cond_t_", (int)sizeof(struct pthread_cond_t_));
  printf("%30s %4d\n", "pthread_condattr_t_", (int)sizeof(struct pthread_condattr_t_));
  printf("%30s %4d\n", "pthread_rwlock_t_", (int)sizeof(struct pthread_rwlock_t_));
  printf("%30s %4d\n", "pthread_rwlockattr_t_", (int)sizeof(struct pthread_rwlockattr_t_));
  printf("%30s %4d\n", "pthread_once_t_", (int)sizeof(struct pthread_once_t_));
  printf("%30s %4d\n", "ptw32_cleanup_t", (int)sizeof(struct ptw32_cleanup_t));
  printf("%30s %4d\n", "ptw32_mcs_node_t_", (int)sizeof(struct ptw32_mcs_node_t_));
  printf("%30s %4d\n", "sched_param", (int)sizeof(struct sched_param));
  printf("-------------------------------\n");

  return 0;
}