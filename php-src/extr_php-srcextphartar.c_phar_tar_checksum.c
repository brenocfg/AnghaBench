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
typedef  unsigned char uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t phar_tar_checksum(char *buf, size_t len) /* {{{ */
{
	uint32_t sum = 0;
	char *end = buf + len;

	while (buf != end) {
		sum += (unsigned char)*buf;
		++buf;
	}
	return sum;
}