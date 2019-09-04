#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ num; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  QE_SNUM_STATE_FREE ; 
 int qe_num_of_snum ; 
 TYPE_1__* snums ; 

void qe_put_snum(u8 snum)
{
	int i;

	for (i = 0; i < qe_num_of_snum; i++) {
		if (snums[i].num == snum) {
			snums[i].state = QE_SNUM_STATE_FREE;
			break;
		}
	}
}