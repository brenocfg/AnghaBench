#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct demux_stream {int eof; int need_wakeup; scalar_t__ fw_packs; scalar_t__ fw_bytes; int /*<<< orphan*/ * reader_head; TYPE_1__* in; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_bytes; } ;

/* Variables and functions */

__attribute__((used)) static void ds_clear_reader_queue_state(struct demux_stream *ds)
{
    ds->in->fw_bytes -= ds->fw_bytes;
    ds->reader_head = NULL;
    ds->fw_bytes = 0;
    ds->fw_packs = 0;
    ds->eof = false;
    ds->need_wakeup = true;
}