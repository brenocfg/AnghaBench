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
typedef  scalar_t__ uint8 ;

/* Variables and functions */

__attribute__((used)) static uint8 *
check_eme_pkcs1_v15(uint8 *data, int len)
{
	uint8	   *data_end = data + len;
	uint8	   *p = data;
	int			rnd = 0;

	if (len < 1 + 8 + 1)
		return NULL;

	if (*p++ != 2)
		return NULL;

	while (p < data_end && *p)
	{
		p++;
		rnd++;
	}

	if (p == data_end)
		return NULL;
	if (*p != 0)
		return NULL;
	if (rnd < 8)
		return NULL;
	return p + 1;
}