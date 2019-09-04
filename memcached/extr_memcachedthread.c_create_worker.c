#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_2__ {int /*<<< orphan*/  thread_id; } ;
typedef  TYPE_1__ LIBEVENT_THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static void create_worker(void *(*func)(void *), void *arg) {
    pthread_attr_t  attr;
    int             ret;

    pthread_attr_init(&attr);

    if ((ret = pthread_create(&((LIBEVENT_THREAD*)arg)->thread_id, &attr, func, arg)) != 0) {
        fprintf(stderr, "Can't create thread: %s\n",
                strerror(ret));
        exit(1);
    }
}