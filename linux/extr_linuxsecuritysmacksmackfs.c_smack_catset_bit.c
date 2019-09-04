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
 int SMK_CIPSOLEN ; 

__attribute__((used)) static inline void smack_catset_bit(unsigned int cat, char *catsetp)
{
	if (cat == 0 || cat > (SMK_CIPSOLEN * 8))
		return;

	catsetp[(cat - 1) / 8] |= 0x80 >> ((cat - 1) % 8);
}