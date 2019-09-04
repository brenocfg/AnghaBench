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
typedef  int ulong ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
qla27xx_template_checksum(void *p, ulong size)
{
	uint32_t *buf = p;
	uint64_t sum = 0;

	size /= sizeof(*buf);

	while (size--)
		sum += *buf++;

	sum = (sum & 0xffffffff) + (sum >> 32);

	return ~sum;
}