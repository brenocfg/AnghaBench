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
typedef  int /*<<< orphan*/  u8 ;
struct fusb300 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB300_EPSET0_STL ; 
 int /*<<< orphan*/  FUSB300_OFFSET_EPSET0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fusb300_enable_bit (struct fusb300*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fusb300_set_epnstall(struct fusb300 *fusb300, u8 ep)
{
	fusb300_enable_bit(fusb300, FUSB300_OFFSET_EPSET0(ep),
		FUSB300_EPSET0_STL);
}