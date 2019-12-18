#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  out; int /*<<< orphan*/  pretty; } ;
typedef  TYPE_1__ json_writer_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsonw_indent (TYPE_1__*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonw_eol(json_writer_t *self)
{
	if (!self->pretty)
		return;

	putc('\n', self->out);
	jsonw_indent(self);
}