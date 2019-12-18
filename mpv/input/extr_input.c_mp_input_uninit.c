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
struct input_ctx {int /*<<< orphan*/  mutex; struct input_ctx* current_down_cmd; int /*<<< orphan*/  cmd_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_input_sources (struct input_ctx*) ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reload_opts (struct input_ctx*,int) ; 
 int /*<<< orphan*/  talloc_free (struct input_ctx*) ; 

void mp_input_uninit(struct input_ctx *ictx)
{
    if (!ictx)
        return;

    input_lock(ictx);
    reload_opts(ictx, true);
    input_unlock(ictx);

    close_input_sources(ictx);
    clear_queue(&ictx->cmd_queue);
    talloc_free(ictx->current_down_cmd);
    pthread_mutex_destroy(&ictx->mutex);
    talloc_free(ictx);
}