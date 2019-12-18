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
struct demux_stream {int eof; int need_wakeup; int /*<<< orphan*/ * reader_head; } ;

/* Variables and functions */

__attribute__((used)) static void ds_clear_reader_queue_state(struct demux_stream *ds)
{
    ds->reader_head = NULL;
    ds->eof = false;
    ds->need_wakeup = true;
}