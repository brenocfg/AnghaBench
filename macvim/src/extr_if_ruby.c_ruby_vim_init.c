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

/* Variables and functions */
 int /*<<< orphan*/  INT2NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIM_VERSION_BUILD ; 
 int /*<<< orphan*/  VIM_VERSION_LONG ; 
 int /*<<< orphan*/  VIM_VERSION_LONG_DATE ; 
 int /*<<< orphan*/  VIM_VERSION_MAJOR ; 
 int /*<<< orphan*/  VIM_VERSION_MEDIUM ; 
 int /*<<< orphan*/  VIM_VERSION_MINOR ; 
 int /*<<< orphan*/  VIM_VERSION_PATCHLEVEL ; 
 int /*<<< orphan*/  VIM_VERSION_SHORT ; 
 int /*<<< orphan*/  buffer_append ; 
 int /*<<< orphan*/  buffer_aref ; 
 int /*<<< orphan*/  buffer_aset ; 
 int /*<<< orphan*/  buffer_count ; 
 int /*<<< orphan*/  buffer_delete ; 
 int /*<<< orphan*/  buffer_name ; 
 int /*<<< orphan*/  buffer_number ; 
 int /*<<< orphan*/  buffer_s_aref ; 
 int /*<<< orphan*/  buffer_s_count ; 
 int /*<<< orphan*/  buffer_s_current ; 
 void* cBuffer ; 
 void* cVimWindow ; 
 int /*<<< orphan*/  current_line_number ; 
 void* eDeletedBufferError ; 
 void* eDeletedWindowError ; 
 int /*<<< orphan*/  line_s_current ; 
 int /*<<< orphan*/  mVIM ; 
 int /*<<< orphan*/  objtbl ; 
 int /*<<< orphan*/  rb_cObject ; 
 void* rb_define_class_under (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_define_const (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_define_method (void*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_define_module (char*) ; 
 int /*<<< orphan*/  rb_define_module_function (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_define_singleton_method (void*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_define_virtual_variable (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_eStandardError ; 
 int /*<<< orphan*/  rb_global_variable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_hash_new () ; 
 int /*<<< orphan*/  rb_str_new2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_line ; 
 int /*<<< orphan*/  vim_command ; 
 int /*<<< orphan*/  vim_evaluate ; 
 int /*<<< orphan*/  vim_message ; 
 int /*<<< orphan*/  vim_set_option ; 
 int /*<<< orphan*/  window_buffer ; 
 int /*<<< orphan*/  window_cursor ; 
 int /*<<< orphan*/  window_height ; 
 int /*<<< orphan*/  window_s_aref ; 
 int /*<<< orphan*/  window_s_count ; 
 int /*<<< orphan*/  window_s_current ; 
 int /*<<< orphan*/  window_set_cursor ; 
 int /*<<< orphan*/  window_set_height ; 
 int /*<<< orphan*/  window_set_width ; 
 int /*<<< orphan*/  window_width ; 

__attribute__((used)) static void ruby_vim_init(void)
{
    objtbl = rb_hash_new();
    rb_global_variable(&objtbl);

    /* The Vim module used to be called "VIM", but "Vim" is better.  Make an
     * alias "VIM" for backwards compatibility. */
    mVIM = rb_define_module("Vim");
    rb_define_const(rb_cObject, "VIM", mVIM);
    rb_define_const(mVIM, "VERSION_MAJOR", INT2NUM(VIM_VERSION_MAJOR));
    rb_define_const(mVIM, "VERSION_MINOR", INT2NUM(VIM_VERSION_MINOR));
    rb_define_const(mVIM, "VERSION_BUILD", INT2NUM(VIM_VERSION_BUILD));
    rb_define_const(mVIM, "VERSION_PATCHLEVEL", INT2NUM(VIM_VERSION_PATCHLEVEL));
    rb_define_const(mVIM, "VERSION_SHORT", rb_str_new2(VIM_VERSION_SHORT));
    rb_define_const(mVIM, "VERSION_MEDIUM", rb_str_new2(VIM_VERSION_MEDIUM));
    rb_define_const(mVIM, "VERSION_LONG", rb_str_new2(VIM_VERSION_LONG));
    rb_define_const(mVIM, "VERSION_LONG_DATE", rb_str_new2(VIM_VERSION_LONG_DATE));
    rb_define_module_function(mVIM, "message", vim_message, 1);
    rb_define_module_function(mVIM, "set_option", vim_set_option, 1);
    rb_define_module_function(mVIM, "command", vim_command, 1);
    rb_define_module_function(mVIM, "evaluate", vim_evaluate, 1);

    eDeletedBufferError = rb_define_class_under(mVIM, "DeletedBufferError",
						rb_eStandardError);
    eDeletedWindowError = rb_define_class_under(mVIM, "DeletedWindowError",
						rb_eStandardError);

    cBuffer = rb_define_class_under(mVIM, "Buffer", rb_cObject);
    rb_define_singleton_method(cBuffer, "current", buffer_s_current, 0);
    rb_define_singleton_method(cBuffer, "count", buffer_s_count, 0);
    rb_define_singleton_method(cBuffer, "[]", buffer_s_aref, 1);
    rb_define_method(cBuffer, "name", buffer_name, 0);
    rb_define_method(cBuffer, "number", buffer_number, 0);
    rb_define_method(cBuffer, "count", buffer_count, 0);
    rb_define_method(cBuffer, "length", buffer_count, 0);
    rb_define_method(cBuffer, "[]", buffer_aref, 1);
    rb_define_method(cBuffer, "[]=", buffer_aset, 2);
    rb_define_method(cBuffer, "delete", buffer_delete, 1);
    rb_define_method(cBuffer, "append", buffer_append, 2);

    /* Added line manipulation functions
     *   SegPhault - 03/07/05 */
    rb_define_method(cBuffer, "line_number", current_line_number, 0);
    rb_define_method(cBuffer, "line", line_s_current, 0);
    rb_define_method(cBuffer, "line=", set_current_line, 1);


    cVimWindow = rb_define_class_under(mVIM, "Window", rb_cObject);
    rb_define_singleton_method(cVimWindow, "current", window_s_current, 0);
    rb_define_singleton_method(cVimWindow, "count", window_s_count, 0);
    rb_define_singleton_method(cVimWindow, "[]", window_s_aref, 1);
    rb_define_method(cVimWindow, "buffer", window_buffer, 0);
    rb_define_method(cVimWindow, "height", window_height, 0);
    rb_define_method(cVimWindow, "height=", window_set_height, 1);
    rb_define_method(cVimWindow, "width", window_width, 0);
    rb_define_method(cVimWindow, "width=", window_set_width, 1);
    rb_define_method(cVimWindow, "cursor", window_cursor, 0);
    rb_define_method(cVimWindow, "cursor=", window_set_cursor, 1);

    rb_define_virtual_variable("$curbuf", buffer_s_current, 0);
    rb_define_virtual_variable("$curwin", window_s_current, 0);
}