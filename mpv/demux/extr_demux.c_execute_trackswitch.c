#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct demux_internal {int tracks_switched; int num_streams; int /*<<< orphan*/  lock; TYPE_4__* d_thread; TYPE_2__** streams; } ;
struct TYPE_8__ {TYPE_3__* desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* switched_tracks ) (TYPE_4__*) ;} ;
struct TYPE_6__ {TYPE_1__* ds; } ;
struct TYPE_5__ {int selected; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void execute_trackswitch(struct demux_internal *in)
{
    in->tracks_switched = false;

    bool any_selected = false;
    for (int n = 0; n < in->num_streams; n++)
        any_selected |= in->streams[n]->ds->selected;

    pthread_mutex_unlock(&in->lock);

    if (in->d_thread->desc->switched_tracks)
        in->d_thread->desc->switched_tracks(in->d_thread);

    pthread_mutex_lock(&in->lock);
}