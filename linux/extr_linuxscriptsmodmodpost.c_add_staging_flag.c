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
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_printf (struct buffer*,char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 

__attribute__((used)) static void add_staging_flag(struct buffer *b, const char *name)
{
	if (strstarts(name, "drivers/staging"))
		buf_printf(b, "\nMODULE_INFO(staging, \"Y\");\n");
}