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
typedef  scalar_t__ Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 scalar_t__ InvalidSnapshot ; 
 scalar_t__ RegisterSnapshotOnOwner (scalar_t__,int /*<<< orphan*/ ) ; 

Snapshot
RegisterSnapshot(Snapshot snapshot)
{
	if (snapshot == InvalidSnapshot)
		return InvalidSnapshot;

	return RegisterSnapshotOnOwner(snapshot, CurrentResourceOwner);
}