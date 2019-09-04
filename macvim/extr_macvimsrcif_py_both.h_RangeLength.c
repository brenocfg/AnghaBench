#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int end; int start; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RangeObject ;
typedef  int PyInt ;

/* Variables and functions */
 scalar_t__ CheckBuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyInt
RangeLength(RangeObject *self)
{
    /* HOW DO WE SIGNAL AN ERROR FROM THIS FUNCTION? */
    if (CheckBuffer(self->buf))
	return -1; /* ??? */

    return (self->end - self->start + 1);
}