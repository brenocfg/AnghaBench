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
struct TYPE_2__ {scalar_t__ w_pos; char const** w; } ;
struct tomoyo_io_buffer {TYPE_1__ r; } ;

/* Variables and functions */
 scalar_t__ TOMOYO_MAX_IO_READ_QUEUE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  tomoyo_flush (struct tomoyo_io_buffer*) ; 

__attribute__((used)) static void tomoyo_set_string(struct tomoyo_io_buffer *head, const char *string)
{
	if (head->r.w_pos < TOMOYO_MAX_IO_READ_QUEUE) {
		head->r.w[head->r.w_pos++] = string;
		tomoyo_flush(head);
	} else
		WARN_ON(1);
}