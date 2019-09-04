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
struct tomoyo_io_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tomoyo_set_string (struct tomoyo_io_buffer*,char*) ; 

__attribute__((used)) static void tomoyo_set_space(struct tomoyo_io_buffer *head)
{
	tomoyo_set_string(head, " ");
}