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
typedef  int /*<<< orphan*/  Portal ;
typedef  int /*<<< orphan*/  FetchDirection ;

/* Variables and functions */
 int /*<<< orphan*/  None_Receiver ; 
 int /*<<< orphan*/  _SPI_cursor_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

void
SPI_scroll_cursor_move(Portal portal, FetchDirection direction, long count)
{
	_SPI_cursor_operation(portal, direction, count, None_Receiver);
}