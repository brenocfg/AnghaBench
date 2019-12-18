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
typedef  int /*<<< orphan*/  BufferUsage ;

/* Variables and functions */
 int /*<<< orphan*/  BufferUsageAccumDiff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgBufferUsage ; 
 int /*<<< orphan*/  save_pgBufferUsage ; 

void
InstrEndParallelQuery(BufferUsage *result)
{
	memset(result, 0, sizeof(BufferUsage));
	BufferUsageAccumDiff(result, &pgBufferUsage, &save_pgBufferUsage);
}