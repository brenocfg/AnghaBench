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
struct tep_event_filter {char* error_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  tep_buffer_init (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_init_error_buf(struct tep_event_filter *filter)
{
	/* clear buffer to reset show error */
	tep_buffer_init("", 0);
	filter->error_buffer[0] = '\0';
}