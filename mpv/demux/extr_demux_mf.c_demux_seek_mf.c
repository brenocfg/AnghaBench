#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nr_of_files; int curr_frame; TYPE_2__* sh; } ;
typedef  TYPE_3__ mf_t ;
struct TYPE_9__ {TYPE_3__* priv; } ;
typedef  TYPE_4__ demuxer_t ;
struct TYPE_7__ {TYPE_1__* codec; } ;
struct TYPE_6__ {double fps; } ;

/* Variables and functions */
 int SEEK_FACTOR ; 

__attribute__((used)) static void demux_seek_mf(demuxer_t *demuxer, double seek_pts, int flags)
{
    mf_t *mf = demuxer->priv;
    int newpos = seek_pts * mf->sh->codec->fps;
    if (flags & SEEK_FACTOR)
        newpos = seek_pts * (mf->nr_of_files - 1);
    if (newpos < 0)
        newpos = 0;
    if (newpos >= mf->nr_of_files)
        newpos = mf->nr_of_files;
    mf->curr_frame = newpos;
}