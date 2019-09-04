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
typedef  int /*<<< orphan*/  temp_l_pg ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int resp_temp_l_pg(unsigned char *arr)
{
	unsigned char temp_l_pg[] = {0x0, 0x0, 0x3, 0x2, 0x0, 38,
				     0x0, 0x1, 0x3, 0x2, 0x0, 65,
		};

	memcpy(arr, temp_l_pg, sizeof(temp_l_pg));
	return sizeof(temp_l_pg);
}