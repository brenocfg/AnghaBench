#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* avfc; } ;
typedef  TYPE_2__ lavf_priv_t ;
struct TYPE_8__ {int /*<<< orphan*/  metadata; TYPE_2__* priv; } ;
typedef  TYPE_3__ demuxer_t ;
struct TYPE_6__ {int event_flags; int /*<<< orphan*/  metadata; } ;

/* Variables and functions */
 int AVFMT_EVENT_FLAG_METADATA_UPDATED ; 
 int /*<<< orphan*/  demux_metadata_changed (TYPE_3__*) ; 
 int /*<<< orphan*/  mp_tags_copy_from_av_dictionary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_metadata(demuxer_t *demuxer)
{
    lavf_priv_t *priv = demuxer->priv;
    if (priv->avfc->event_flags & AVFMT_EVENT_FLAG_METADATA_UPDATED) {
        mp_tags_copy_from_av_dictionary(demuxer->metadata, priv->avfc->metadata);
        priv->avfc->event_flags = 0;
        demux_metadata_changed(demuxer);
    }
}