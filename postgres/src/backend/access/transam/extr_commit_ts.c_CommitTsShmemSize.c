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
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  CommitTimestampShared ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTsShmemBuffers () ; 
 scalar_t__ SimpleLruShmemSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Size
CommitTsShmemSize(void)
{
	return SimpleLruShmemSize(CommitTsShmemBuffers(), 0) +
		sizeof(CommitTimestampShared);
}