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

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int select_rom(unsigned int pitch)
{
	if (pitch > 0x00428f5c && pitch < 0x01b851ec) {
		/* 0.26 <= pitch <= 1.72 */
		return 1;
	} else if (pitch == 0x01d66666 || pitch == 0x01d66667) {
		/* pitch == 1.8375 */
		return 2;
	} else if (pitch == 0x02000000) {
		/* pitch == 2 */
		return 3;
	} else if (pitch <= 0x08000000) {
		/* 0 <= pitch <= 8 */
		return 0;
	} else {
		return -ENOENT;
	}
}