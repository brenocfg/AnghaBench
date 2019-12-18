#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ndigi; } ;
typedef  TYPE_1__ ax25_digi ;

/* Variables and functions */
 int AX25_ADDR_LEN ; 

int ax25_addr_size(const ax25_digi *dp)
{
	if (dp == NULL)
		return 2 * AX25_ADDR_LEN;

	return AX25_ADDR_LEN * (2 + dp->ndigi);
}