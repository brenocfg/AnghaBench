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
struct vo {TYPE_1__* in; struct vo* eq_opts_cache; struct vo* gl_opts_cache; struct vo* opts_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  forget_frames (struct vo*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct vo*) ; 

__attribute__((used)) static void dealloc_vo(struct vo *vo)
{
    forget_frames(vo); // implicitly synchronized

    // These must be free'd before vo->in->dispatch.
    talloc_free(vo->opts_cache);
    talloc_free(vo->gl_opts_cache);
    talloc_free(vo->eq_opts_cache);

    pthread_mutex_destroy(&vo->in->lock);
    pthread_cond_destroy(&vo->in->wakeup);
    talloc_free(vo);
}