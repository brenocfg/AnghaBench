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
struct TYPE_4__ {int pretty; char sep; scalar_t__ depth; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ json_writer_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

json_writer_t *jsonw_new(FILE *f)
{
	json_writer_t *self = malloc(sizeof(*self));
	if (self) {
		self->out = f;
		self->depth = 0;
		self->pretty = false;
		self->sep = '\0';
	}
	return self;
}