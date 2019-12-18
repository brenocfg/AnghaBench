#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char sep; int /*<<< orphan*/  out; scalar_t__ pretty; } ;
typedef  TYPE_1__ json_writer_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsonw_eol (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonw_eor (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonw_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

void jsonw_name(json_writer_t *self, const char *name)
{
	jsonw_eor(self);
	jsonw_eol(self);
	self->sep = '\0';
	jsonw_puts(self, name);
	putc(':', self->out);
	if (self->pretty)
		putc(' ', self->out);
}