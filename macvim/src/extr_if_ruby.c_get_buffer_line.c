#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ linenr_T ;
struct TYPE_5__ {scalar_t__ ml_line_count; } ;
struct TYPE_6__ {TYPE_1__ b_ml; } ;
typedef  TYPE_2__ buf_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ml_get_buf (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_eIndexError ; 
 int /*<<< orphan*/  rb_raise (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  vim_str2rb_enc_str (char*) ; 

__attribute__((used)) static VALUE get_buffer_line(buf_T *buf, linenr_T n)
{
    if (n <= 0 || n > buf->b_ml.ml_line_count)
	rb_raise(rb_eIndexError, "line number %ld out of range", (long)n);
    return vim_str2rb_enc_str((char *)ml_get_buf(buf, n, FALSE));
}