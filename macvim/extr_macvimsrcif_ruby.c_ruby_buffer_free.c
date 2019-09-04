#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ b_ruby_ref; } ;
typedef  TYPE_1__ buf_T ;
typedef  int /*<<< orphan*/  VALUE ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Qnil ; 
 TYPE_3__* RDATA (scalar_t__) ; 
 int /*<<< orphan*/  objtbl ; 
 int /*<<< orphan*/  rb_hash_aset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_obj_id (int /*<<< orphan*/ ) ; 

void ruby_buffer_free(buf_T *buf)
{
    if (buf->b_ruby_ref)
    {
	rb_hash_aset(objtbl, rb_obj_id((VALUE) buf->b_ruby_ref), Qnil);
	RDATA(buf->b_ruby_ref)->data = NULL;
    }
}