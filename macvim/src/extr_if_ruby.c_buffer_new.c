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
struct TYPE_4__ {void* b_ruby_ref; } ;
typedef  TYPE_1__ buf_T ;
typedef  scalar_t__ VALUE ;

/* Variables and functions */
 scalar_t__ Data_Wrap_Struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cBuffer ; 
 int /*<<< orphan*/  objtbl ; 
 int /*<<< orphan*/  rb_hash_aset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rb_obj_id (scalar_t__) ; 

__attribute__((used)) static VALUE buffer_new(buf_T *buf)
{
    if (buf->b_ruby_ref)
    {
	return (VALUE) buf->b_ruby_ref;
    }
    else
    {
	VALUE obj = Data_Wrap_Struct(cBuffer, 0, 0, buf);
	buf->b_ruby_ref = (void *) obj;
	rb_hash_aset(objtbl, rb_obj_id(obj), obj);
	return obj;
    }
}