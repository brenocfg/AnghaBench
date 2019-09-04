#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  linenr_T ;
typedef  int /*<<< orphan*/  buf_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 scalar_t__ NUM2LONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE buffer_aset(VALUE self, VALUE num, VALUE str)
{
    buf_T *buf = get_buf(self);

    if (buf != NULL)
	return set_buffer_line(buf, (linenr_T)NUM2LONG(num), str);
    return str;
}