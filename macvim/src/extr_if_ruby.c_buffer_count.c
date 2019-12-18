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
struct TYPE_4__ {int /*<<< orphan*/  ml_line_count; } ;
struct TYPE_5__ {TYPE_1__ b_ml; } ;
typedef  TYPE_2__ buf_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  INT2NUM (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE buffer_count(VALUE self)
{
    buf_T *buf = get_buf(self);

    return INT2NUM(buf->b_ml.ml_line_count);
}