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
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HistoricSnapshotActive () ; 
 int /*<<< orphan*/ * tuplecid_data ; 

HTAB *
HistoricSnapshotGetTupleCids(void)
{
	Assert(HistoricSnapshotActive());
	return tuplecid_data;
}