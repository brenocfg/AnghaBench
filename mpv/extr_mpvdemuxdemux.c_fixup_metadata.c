#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct demux_stream {TYPE_3__* tags_init; int /*<<< orphan*/  tags_reader; } ;
struct demux_internal {int num_streams; TYPE_1__* d_thread; TYPE_2__** streams; } ;
struct TYPE_7__ {int /*<<< orphan*/  demux; } ;
struct TYPE_6__ {struct demux_stream* ds; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_packet_tags_make_writable (TYPE_3__**) ; 
 int /*<<< orphan*/  mp_packet_tags_setref (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mp_tags_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fixup_metadata(struct demux_internal *in)
{
    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;
        mp_packet_tags_make_writable(&ds->tags_init);
        mp_tags_replace(ds->tags_init->demux, in->d_thread->metadata);
        mp_packet_tags_setref(&ds->tags_reader, ds->tags_init);
    }
}