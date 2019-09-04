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
typedef  int /*<<< orphan*/  u16 ;
struct hermes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EZUSB_RID_TX ; 

__attribute__((used)) static int ezusb_allocate(struct hermes *hw, u16 size, u16 *fid)
{
	*fid = EZUSB_RID_TX;
	return 0;
}