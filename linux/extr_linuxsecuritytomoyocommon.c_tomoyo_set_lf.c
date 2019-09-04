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
struct TYPE_2__ {int /*<<< orphan*/  w_pos; } ;
struct tomoyo_io_buffer {TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  tomoyo_set_string (struct tomoyo_io_buffer*,char*) ; 

__attribute__((used)) static bool tomoyo_set_lf(struct tomoyo_io_buffer *head)
{
	tomoyo_set_string(head, "\n");
	return !head->r.w_pos;
}