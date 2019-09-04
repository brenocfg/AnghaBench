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
struct dgnc_board {TYPE_2__* print_driver; TYPE_1__* serial_driver; } ;
struct TYPE_4__ {unsigned int major; } ;
struct TYPE_3__ {unsigned int major; } ;

/* Variables and functions */
 int MAXBOARDS ; 
 struct dgnc_board** dgnc_board ; 

__attribute__((used)) static struct dgnc_board *find_board_by_major(unsigned int major)
{
	int i;

	for (i = 0; i < MAXBOARDS; i++) {
		struct dgnc_board *brd = dgnc_board[i];

		if (!brd)
			return NULL;

		if (major == brd->serial_driver->major ||
		    major == brd->print_driver->major)
			return brd;
	}

	return NULL;
}