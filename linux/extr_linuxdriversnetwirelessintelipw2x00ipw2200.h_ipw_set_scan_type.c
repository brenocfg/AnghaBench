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
typedef  int u8 ;
struct ipw_scan_request_ext {int* scan_type; } ;

/* Variables and functions */

__attribute__((used)) static inline void ipw_set_scan_type(struct ipw_scan_request_ext *scan,
				     u8 index, u8 scan_type)
{
	if (index % 2)
		scan->scan_type[index / 2] =
		    (scan->scan_type[index / 2] & 0xF0) | (scan_type & 0x0F);
	else
		scan->scan_type[index / 2] =
		    (scan->scan_type[index / 2] & 0x0F) |
		    ((scan_type & 0x0F) << 4);
}