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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpGistInitPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
SpGistInitBuffer(Buffer b, uint16 f)
{
	Assert(BufferGetPageSize(b) == BLCKSZ);
	SpGistInitPage(BufferGetPage(b), f);
}