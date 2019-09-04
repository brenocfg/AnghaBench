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
struct TYPE_4__ {char sep; int /*<<< orphan*/  depth; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ json_writer_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsonw_eor (TYPE_1__*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonw_begin(json_writer_t *self, int c)
{
	jsonw_eor(self);
	putc(c, self->out);
	++self->depth;
	self->sep = '\0';
}