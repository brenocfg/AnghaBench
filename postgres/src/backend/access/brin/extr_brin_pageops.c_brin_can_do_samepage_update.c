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
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetExactFreeSpace (int /*<<< orphan*/ ) ; 

bool
brin_can_do_samepage_update(Buffer buffer, Size origsz, Size newsz)
{
	return
		((newsz <= origsz) ||
		 PageGetExactFreeSpace(BufferGetPage(buffer)) >= (newsz - origsz));
}