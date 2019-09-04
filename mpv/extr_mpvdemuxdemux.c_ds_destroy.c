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
struct demux_stream {int /*<<< orphan*/  tags_demux; int /*<<< orphan*/  tags_reader; int /*<<< orphan*/  tags_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_packet_tags_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds_destroy(void *ptr)
{
    struct demux_stream *ds = ptr;
    mp_packet_tags_unref(ds->tags_init);
    mp_packet_tags_unref(ds->tags_reader);
    mp_packet_tags_unref(ds->tags_demux);
}