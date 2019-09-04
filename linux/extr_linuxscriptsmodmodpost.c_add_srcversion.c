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
struct module {scalar_t__* srcversion; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 

__attribute__((used)) static void add_srcversion(struct buffer *b, struct module *mod)
{
	if (mod->srcversion[0]) {
		buf_printf(b, "\n");
		buf_printf(b, "MODULE_INFO(srcversion, \"%s\");\n",
			   mod->srcversion);
	}
}