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
typedef  int __u16 ;

/* Variables and functions */
 void* hex_asc_lo (int) ; 

__attribute__((used)) static inline int append_filetype_suffix(char *buf, __u16 filetype)
{
	if (filetype == 0xffff)	/* no explicit 12-bit file type was set */
		return 0;

	*buf++ = ',';
	*buf++ = hex_asc_lo(filetype >> 8);
	*buf++ = hex_asc_lo(filetype >> 4);
	*buf++ = hex_asc_lo(filetype >> 0);
	return 4;
}