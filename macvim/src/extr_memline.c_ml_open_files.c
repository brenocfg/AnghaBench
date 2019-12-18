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
struct TYPE_4__ {scalar_t__ b_changed; int /*<<< orphan*/  b_p_ro; struct TYPE_4__* b_next; } ;
typedef  TYPE_1__ buf_T ;

/* Variables and functions */
 TYPE_1__* firstbuf ; 
 int /*<<< orphan*/  ml_open_file (TYPE_1__*) ; 

void
ml_open_files()
{
    buf_T	*buf;

    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	if (!buf->b_p_ro || buf->b_changed)
	    ml_open_file(buf);
}