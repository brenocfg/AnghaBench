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
typedef  enum kmsg_dump_reason { ____Placeholder_kmsg_dump_reason } kmsg_dump_reason ;

/* Variables and functions */
#define  KMSG_DUMP_EMERG 133 
#define  KMSG_DUMP_HALT 132 
#define  KMSG_DUMP_OOPS 131 
#define  KMSG_DUMP_PANIC 130 
#define  KMSG_DUMP_POWEROFF 129 
#define  KMSG_DUMP_RESTART 128 

__attribute__((used)) static const char *get_reason_str(enum kmsg_dump_reason reason)
{
	switch (reason) {
	case KMSG_DUMP_PANIC:
		return "Panic";
	case KMSG_DUMP_OOPS:
		return "Oops";
	case KMSG_DUMP_EMERG:
		return "Emergency";
	case KMSG_DUMP_RESTART:
		return "Restart";
	case KMSG_DUMP_HALT:
		return "Halt";
	case KMSG_DUMP_POWEROFF:
		return "Poweroff";
	default:
		return "Unknown";
	}
}