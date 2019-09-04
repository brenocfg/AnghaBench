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
typedef  size_t u8 ;

/* Variables and functions */
 size_t MAX_SSID_LEN ; 
 int TAG_PARAM_OFFSET ; 

__attribute__((used)) static inline void get_ssid(u8 *data, u8 *ssid, u8 *p_ssid_len)
{
	u8 i, j, len;

	len = data[TAG_PARAM_OFFSET + 1];
	j   = TAG_PARAM_OFFSET + 2;

	if (len >= MAX_SSID_LEN)
		len = 0;

	for (i = 0; i < len; i++, j++)
		ssid[i] = data[j];

	ssid[len] = '\0';

	*p_ssid_len = len;
}