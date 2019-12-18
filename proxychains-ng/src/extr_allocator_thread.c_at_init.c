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
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int MAP_ANON ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_INIT (void*) ; 
 int /*<<< orphan*/  PFUNC () ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  PTHREAD_STACK_MIN ; 
 int /*<<< orphan*/  allocator_thread ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  initpipe (int /*<<< orphan*/ ) ; 
 void* internal_ips ; 
 void* internal_ips_lock ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* mmap (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_pipefd ; 
 int /*<<< orphan*/  resp_pipefd ; 
 int /*<<< orphan*/  threadfunc ; 

void at_init(void) {
	PFUNC();
	void *shm = mmap(0, 4096, PROT_WRITE|PROT_READ, MAP_ANON|MAP_SHARED, -1, 0);
	assert(shm);
	internal_ips_lock = shm;
	internal_ips = (void*)((char*)shm + 2048);

	MUTEX_INIT(internal_ips_lock);
	memset(internal_ips, 0, sizeof *internal_ips);
	initpipe(req_pipefd);
	initpipe(resp_pipefd);
	pthread_attr_t allocator_thread_attr;
	pthread_attr_init(&allocator_thread_attr);
	pthread_attr_setstacksize(&allocator_thread_attr, MAX(16 * 1024, PTHREAD_STACK_MIN));
	pthread_create(&allocator_thread, &allocator_thread_attr, threadfunc, 0);
	pthread_attr_destroy(&allocator_thread_attr);
}