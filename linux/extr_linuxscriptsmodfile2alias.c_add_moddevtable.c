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
struct TYPE_2__ {int /*<<< orphan*/  p; int /*<<< orphan*/  pos; } ;
struct module {TYPE_1__ dev_table_buf; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_printf (struct buffer*,char*) ; 
 int /*<<< orphan*/  buf_write (struct buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void add_moddevtable(struct buffer *buf, struct module *mod)
{
	buf_printf(buf, "\n");
	buf_write(buf, mod->dev_table_buf.p, mod->dev_table_buf.pos);
	free(mod->dev_table_buf.p);
}