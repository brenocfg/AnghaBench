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
struct TYPE_3__ {int isFree; int /*<<< orphan*/ * connection; } ;
typedef  TYPE_1__ ParallelSlot ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */

__attribute__((used)) static void
init_slot(ParallelSlot *slot, PGconn *conn)
{
	slot->connection = conn;
	/* Initially assume connection is idle */
	slot->isFree = true;
}