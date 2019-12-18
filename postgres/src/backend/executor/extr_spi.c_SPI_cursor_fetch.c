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

/* Variables and functions */
 int /*<<< orphan*/  CreateDestReceiver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestSPI ; 
 int /*<<< orphan*/  FETCH_BACKWARD ; 
 int /*<<< orphan*/  FETCH_FORWARD ; 
 int /*<<< orphan*/  _SPI_cursor_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

void
SPI_cursor_fetch(Portal portal, bool forward, long count)
{
	_SPI_cursor_operation(portal,
						  forward ? FETCH_FORWARD : FETCH_BACKWARD, count,
						  CreateDestReceiver(DestSPI));
	/* we know that the DestSPI receiver doesn't need a destroy call */
}