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
struct TYPE_3__ {int /*<<< orphan*/  text; scalar_t__ indent; } ;
typedef  TYPE_1__ mxwriter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static inline void writer_dec_indent(mxwriter *This)
{
    if (This->indent) This->indent--;
    /* depth is decreased only when element is closed, meaning it's not a text node
       at this point */
    This->text = FALSE;
}