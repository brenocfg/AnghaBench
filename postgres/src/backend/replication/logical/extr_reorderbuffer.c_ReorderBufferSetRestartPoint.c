#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_3__ {int /*<<< orphan*/  current_restart_decoding_lsn; } ;
typedef  TYPE_1__ ReorderBuffer ;

/* Variables and functions */

void
ReorderBufferSetRestartPoint(ReorderBuffer *rb, XLogRecPtr ptr)
{
	rb->current_restart_decoding_lsn = ptr;
}