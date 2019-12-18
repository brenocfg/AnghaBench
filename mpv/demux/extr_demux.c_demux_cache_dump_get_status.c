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
struct demux_internal {int dumper_status; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int demux_cache_dump_get_status(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    pthread_mutex_lock(&in->lock);
    int status = in->dumper_status;
    pthread_mutex_unlock(&in->lock);
    return status;
}