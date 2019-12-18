#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* b_next; } ;
typedef  TYPE_1__ buf_T ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bufIsChanged (TYPE_1__*) ; 
 TYPE_1__* firstbuf ; 
 int /*<<< orphan*/  ml_close (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
ml_close_notmod()
{
    buf_T	*buf;

    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	if (!bufIsChanged(buf))
	    ml_close(buf, TRUE);    /* close all not-modified buffers */
}