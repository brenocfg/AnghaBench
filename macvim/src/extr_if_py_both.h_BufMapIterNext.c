#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_next; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ BufferObject ;

/* Variables and functions */
 int /*<<< orphan*/ * BufferNew (int /*<<< orphan*/ ) ; 
 scalar_t__ CheckBuffer (TYPE_2__*) ; 

__attribute__((used)) static PyObject *
BufMapIterNext(PyObject **buffer)
{
    PyObject	*next;
    PyObject	*ret;

    if (!*buffer)
	return NULL;

    ret = *buffer;

    if (CheckBuffer((BufferObject *)(ret)))
    {
	*buffer = NULL;
	return NULL;
    }

    if (!((BufferObject *)(ret))->buf->b_next)
	next = NULL;
    else if (!(next = BufferNew(((BufferObject *)(ret))->buf->b_next)))
	return NULL;
    *buffer = next;
    /* Do not increment reference: we no longer hold it (decref), but whoever
     * on other side will hold (incref). Decref+incref = nothing. */
    return ret;
}