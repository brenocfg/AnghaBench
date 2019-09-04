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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ pn533_std_checksum (scalar_t__) ; 

__attribute__((used)) static u8 pn533_std_data_checksum(u8 *data, int datalen)
{
	u8 sum = 0;
	int i;

	for (i = 0; i < datalen; i++)
		sum += data[i];

	return pn533_std_checksum(sum);
}