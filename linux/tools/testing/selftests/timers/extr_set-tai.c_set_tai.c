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
typedef  int /*<<< orphan*/  tx ;
struct timex {int constant; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_TAI ; 
 int adjtimex (struct timex*) ; 
 int /*<<< orphan*/  memset (struct timex*,int /*<<< orphan*/ ,int) ; 

int set_tai(int offset)
{
	struct timex tx;

	memset(&tx, 0, sizeof(tx));

	tx.modes = ADJ_TAI;
	tx.constant = offset;

	return adjtimex(&tx);
}