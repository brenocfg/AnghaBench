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
struct TYPE_3__ {struct TYPE_3__* w_next; } ;
typedef  TYPE_1__ win_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  INT2NUM (int) ; 
 TYPE_1__* firstwin ; 

__attribute__((used)) static VALUE window_s_count()
{
#ifdef FEAT_WINDOWS
    win_T	*w;
    int n = 0;

    for (w = firstwin; w != NULL; w = w->w_next)
	n++;
    return INT2NUM(n);
#else
    return INT2NUM(1);
#endif
}