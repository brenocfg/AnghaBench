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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int CHMOD (char*,size_t) ; 
 char* RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (size_t) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,size_t*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (char const*,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static mrb_value
mrb_file_s_chmod(mrb_state *mrb, mrb_value klass) {
  mrb_int mode;
  mrb_int argc, i;
  mrb_value *filenames;
  int ai = mrb_gc_arena_save(mrb);

  mrb_get_args(mrb, "i*", &mode, &filenames, &argc);
  for (i = 0; i < argc; i++) {
    const char *utf8_path = RSTRING_CSTR(mrb, filenames[i]);
    char *path = mrb_locale_from_utf8(utf8_path, -1);
    if (CHMOD(path, mode) == -1) {
      mrb_locale_free(path);
      mrb_sys_fail(mrb, utf8_path);
    }
    mrb_locale_free(path);
    mrb_gc_arena_restore(mrb, ai);
  }

  return mrb_fixnum_value(argc);
}