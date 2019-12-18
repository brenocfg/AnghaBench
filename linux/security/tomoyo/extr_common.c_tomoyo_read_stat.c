#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct tomoyo_time {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
struct TYPE_2__ {int eof; } ;
struct tomoyo_io_buffer {TYPE_1__ r; } ;

/* Variables and functions */
 size_t TOMOYO_MAX_MEMORY_STAT ; 
 size_t TOMOYO_MAX_POLICY_STAT ; 
 int /*<<< orphan*/  tomoyo_convert_time (scalar_t__,struct tomoyo_time*) ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,unsigned int,...) ; 
 int /*<<< orphan*/ * tomoyo_memory_headers ; 
 unsigned int* tomoyo_memory_quota ; 
 unsigned int* tomoyo_memory_used ; 
 int /*<<< orphan*/ * tomoyo_policy_headers ; 
 int /*<<< orphan*/  tomoyo_set_lf (struct tomoyo_io_buffer*) ; 
 scalar_t__* tomoyo_stat_modified ; 
 int /*<<< orphan*/ * tomoyo_stat_updated ; 

__attribute__((used)) static void tomoyo_read_stat(struct tomoyo_io_buffer *head)
{
	u8 i;
	unsigned int total = 0;

	if (head->r.eof)
		return;
	for (i = 0; i < TOMOYO_MAX_POLICY_STAT; i++) {
		tomoyo_io_printf(head, "Policy %-30s %10u",
				 tomoyo_policy_headers[i],
				 tomoyo_stat_updated[i]);
		if (tomoyo_stat_modified[i]) {
			struct tomoyo_time stamp;

			tomoyo_convert_time(tomoyo_stat_modified[i], &stamp);
			tomoyo_io_printf(head, " (Last: %04u/%02u/%02u %02u:%02u:%02u)",
					 stamp.year, stamp.month, stamp.day,
					 stamp.hour, stamp.min, stamp.sec);
		}
		tomoyo_set_lf(head);
	}
	for (i = 0; i < TOMOYO_MAX_MEMORY_STAT; i++) {
		unsigned int used = tomoyo_memory_used[i];

		total += used;
		tomoyo_io_printf(head, "Memory used by %-22s %10u",
				 tomoyo_memory_headers[i], used);
		used = tomoyo_memory_quota[i];
		if (used)
			tomoyo_io_printf(head, " (Quota: %10u)", used);
		tomoyo_set_lf(head);
	}
	tomoyo_io_printf(head, "Total memory used:                    %10u\n",
			 total);
	head->r.eof = true;
}