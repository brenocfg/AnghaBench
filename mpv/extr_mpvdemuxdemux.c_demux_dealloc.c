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
struct demux_internal {int num_streams; int /*<<< orphan*/  d_user; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  lock; int /*<<< orphan*/ * streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void demux_dealloc(struct demux_internal *in)
{
    for (int n = 0; n < in->num_streams; n++)
        talloc_free(in->streams[n]);
    pthread_mutex_destroy(&in->lock);
    pthread_cond_destroy(&in->wakeup);
    talloc_free(in->d_user);
}