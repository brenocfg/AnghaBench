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
struct mp_input_src {TYPE_1__* in; } ;
struct TYPE_2__ {int init_done; int thread_running; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_rendezvous (int*,int /*<<< orphan*/ ) ; 
 int pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 

void mp_input_src_init_done(struct mp_input_src *src)
{
    assert(!src->in->init_done);
    assert(src->in->thread_running);
    assert(pthread_equal(src->in->thread, pthread_self()));
    src->in->init_done = true;
    mp_rendezvous(&src->in->init_done, 0);
}