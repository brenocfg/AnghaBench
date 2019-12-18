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
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_4__ {TYPE_1__* entries; } ;
struct TYPE_3__ {scalar_t__ lsn; } ;
typedef  TYPE_2__ ReorderBufferIterTXNState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 size_t DatumGetInt32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ReorderBufferIterCompare(Datum a, Datum b, void *arg)
{
	ReorderBufferIterTXNState *state = (ReorderBufferIterTXNState *) arg;
	XLogRecPtr	pos_a = state->entries[DatumGetInt32(a)].lsn;
	XLogRecPtr	pos_b = state->entries[DatumGetInt32(b)].lsn;

	if (pos_a < pos_b)
		return 1;
	else if (pos_a == pos_b)
		return 0;
	return -1;
}