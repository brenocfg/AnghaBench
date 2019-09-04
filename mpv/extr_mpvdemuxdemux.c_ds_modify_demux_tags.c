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
struct demux_stream {int /*<<< orphan*/  tags_demux; int /*<<< orphan*/  tags_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_packet_tags_make_writable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_packet_tags_setref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds_modify_demux_tags(struct demux_stream *ds)
{
    if (!ds->tags_demux)
        mp_packet_tags_setref(&ds->tags_demux, ds->tags_init);
    mp_packet_tags_make_writable(&ds->tags_demux);
}