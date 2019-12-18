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
struct vo_internal {int /*<<< orphan*/  thread; int /*<<< orphan*/  dispatch; } ;
struct vo {struct vo_internal* in; } ;

/* Variables and functions */
 int /*<<< orphan*/  dealloc_vo (struct vo*) ; 
 int /*<<< orphan*/  mp_dispatch_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vo*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminate_vo ; 

void vo_destroy(struct vo *vo)
{
    struct vo_internal *in = vo->in;
    mp_dispatch_run(in->dispatch, terminate_vo, vo);
    pthread_join(vo->in->thread, NULL);
    dealloc_vo(vo);
}