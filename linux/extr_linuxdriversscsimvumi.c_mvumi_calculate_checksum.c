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
struct mvumi_hs_header {scalar_t__ frame_content; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char
mvumi_calculate_checksum(struct mvumi_hs_header *p_header,
							unsigned short len)
{
	unsigned char *ptr;
	unsigned char ret = 0, i;

	ptr = (unsigned char *) p_header->frame_content;
	for (i = 0; i < len; i++) {
		ret ^= *ptr;
		ptr++;
	}

	return ret;
}