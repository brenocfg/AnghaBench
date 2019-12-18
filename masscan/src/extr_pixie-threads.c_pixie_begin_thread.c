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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  void* (* PTHREADFUNC ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 
 size_t _beginthread (void (*) (void*),int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 

size_t
pixie_begin_thread(
    void (*worker_thread)(void*),
    unsigned flags,
    void *worker_data)
{
#if defined(WIN32)
    UNUSEDPARM(flags);
    return _beginthread(worker_thread, 0, worker_data);
#else
    typedef void *(*PTHREADFUNC)(void*);
    pthread_t thread_id = 0;
    pthread_create(
                          &thread_id,
                          NULL,
                          (PTHREADFUNC)worker_thread,
                          worker_data);
    return (size_t)thread_id;
#endif
}