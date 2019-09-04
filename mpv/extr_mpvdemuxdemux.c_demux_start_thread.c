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
struct demuxer {struct demux_internal* in; } ;
struct demux_internal {int threading; int /*<<< orphan*/  thread; struct demuxer* d_user; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  demux_thread ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct demux_internal*) ; 

void demux_start_thread(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    if (!in->threading) {
        in->threading = true;
        if (pthread_create(&in->thread, NULL, demux_thread, in))
            in->threading = false;
    }
}