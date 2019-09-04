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
typedef  unsigned long uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t get_ip_csum(const uint16_t *start, int num_words)
{
	unsigned long sum = 0;
	int i;

	for (i = 0; i < num_words; i++)
		sum += start[i];

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return ~sum;
}