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
struct TYPE_4__ {scalar_t__ depth; char sep; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ json_writer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jsonw_eol (TYPE_1__*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonw_end(json_writer_t *self, int c)
{
	assert(self->depth > 0);

	--self->depth;
	if (self->sep != '\0')
		jsonw_eol(self);
	putc(c, self->out);
	self->sep = ',';
}