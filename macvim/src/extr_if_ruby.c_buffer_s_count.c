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
struct TYPE_3__ {scalar_t__ b_p_bl; struct TYPE_3__* b_next; } ;
typedef  TYPE_1__ buf_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  INT2NUM (int) ; 
 TYPE_1__* firstbuf ; 

__attribute__((used)) static VALUE buffer_s_count()
{
    buf_T *b;
    int n = 0;

    for (b = firstbuf; b != NULL; b = b->b_next)
    {
	/*  Deleted buffers should not be counted
	 *    SegPhault - 01/07/05 */
	if (b->b_p_bl)
	    n++;
    }

    return INT2NUM(n);
}