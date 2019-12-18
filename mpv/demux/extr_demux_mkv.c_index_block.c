#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block_info {int timecode; int duration; int /*<<< orphan*/  track; scalar_t__ keyframe; } ;
struct TYPE_5__ {int tc_scale; int /*<<< orphan*/  cluster_start; } ;
typedef  TYPE_1__ mkv_demuxer_t ;
struct TYPE_6__ {scalar_t__ priv; } ;
typedef  TYPE_2__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_block_position (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void index_block(demuxer_t *demuxer, struct block_info *block)
{
    mkv_demuxer_t *mkv_d = (mkv_demuxer_t *) demuxer->priv;
    if (block->keyframe) {
        add_block_position(demuxer, block->track, mkv_d->cluster_start,
                           block->timecode / mkv_d->tc_scale,
                           block->duration / mkv_d->tc_scale);
    }
}