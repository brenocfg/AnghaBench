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

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 long const event_log_level ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void const*,size_t,int) ; 
 int /*<<< orphan*/  translate_esas2r_event_level_to_kernel (long const) ; 

int esas2r_log_hexdump(const long level,
		       const void *buf,
		       size_t len)
{
	if (level <= event_log_level) {
		print_hex_dump(translate_esas2r_event_level_to_kernel(level),
			       "", DUMP_PREFIX_OFFSET, 16, 1, buf,
			       len, true);
	}

	return 1;
}