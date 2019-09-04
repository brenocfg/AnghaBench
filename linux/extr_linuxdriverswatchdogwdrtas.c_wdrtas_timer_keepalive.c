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
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  RTAS_EVENT_SCAN_ALL_EVENTS ; 
 int /*<<< orphan*/  WDRTAS_LOGBUFFER_LEN ; 
 scalar_t__ __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,long) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 long rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdrtas_logbuffer ; 
 int /*<<< orphan*/  wdrtas_token_event_scan ; 

__attribute__((used)) static void wdrtas_timer_keepalive(void)
{
	long result;

	do {
		result = rtas_call(wdrtas_token_event_scan, 4, 1, NULL,
				   RTAS_EVENT_SCAN_ALL_EVENTS, 0,
				   (void *)__pa(wdrtas_logbuffer),
				   WDRTAS_LOGBUFFER_LEN);
		if (result < 0)
			pr_err("event-scan failed: %li\n", result);
		if (result == 0)
			print_hex_dump(KERN_INFO, "dumping event, data: ",
				DUMP_PREFIX_OFFSET, 16, 1,
				wdrtas_logbuffer, WDRTAS_LOGBUFFER_LEN, false);
	} while (result == 0);
}