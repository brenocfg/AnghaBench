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
struct mp_input_src {int /*<<< orphan*/  (* uninit ) (struct mp_input_src*) ;TYPE_1__* in; int /*<<< orphan*/  (* cancel ) (struct mp_input_src*) ;struct input_ctx* input_ctx; } ;
struct input_ctx {int num_sources; struct mp_input_src** sources; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; scalar_t__ thread_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct mp_input_src**,int,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mp_input_src*) ; 
 int /*<<< orphan*/  stub2 (struct mp_input_src*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_input_src*) ; 

__attribute__((used)) static void mp_input_src_kill(struct mp_input_src *src)
{
    if (!src)
        return;
    struct input_ctx *ictx = src->input_ctx;
    input_lock(ictx);
    for (int n = 0; n < ictx->num_sources; n++) {
        if (ictx->sources[n] == src) {
            MP_TARRAY_REMOVE_AT(ictx->sources, ictx->num_sources, n);
            input_unlock(ictx);
            if (src->cancel)
                src->cancel(src);
            if (src->in->thread_running)
                pthread_join(src->in->thread, NULL);
            if (src->uninit)
                src->uninit(src);
            talloc_free(src);
            return;
        }
    }
    abort();
}