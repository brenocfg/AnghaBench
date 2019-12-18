#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demuxer {int start_time; TYPE_2__* priv; } ;
struct TYPE_4__ {int cluster_tc; TYPE_1__* opts; } ;
typedef  TYPE_2__ mkv_demuxer_t ;
struct TYPE_3__ {int /*<<< orphan*/  probe_start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct demuxer*,char*,int) ; 
 int /*<<< orphan*/  read_next_block_into_queue (struct demuxer*) ; 

__attribute__((used)) static void probe_first_timestamp(struct demuxer *demuxer)
{
    mkv_demuxer_t *mkv_d = demuxer->priv;

    if (!mkv_d->opts->probe_start_time)
        return;

    read_next_block_into_queue(demuxer);

    demuxer->start_time = mkv_d->cluster_tc / 1e9;

    if (demuxer->start_time > 0)
        MP_VERBOSE(demuxer, "Start PTS: %f\n", demuxer->start_time);
}