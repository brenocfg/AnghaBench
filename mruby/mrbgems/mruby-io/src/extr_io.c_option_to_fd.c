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

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
#define  MRB_TT_DATA 129 
#define  MRB_TT_FIXNUM 128 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_static (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_io_fileno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 
 int mrb_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
option_to_fd(mrb_state *mrb, mrb_value hash, const char *key)
{
  mrb_value opt;

  if (!mrb_hash_p(hash)) return -1;
  opt = mrb_hash_fetch(mrb, hash, mrb_symbol_value(mrb_intern_static(mrb, key, strlen(key))), mrb_nil_value());
  if (mrb_nil_p(opt)) return -1;

  switch (mrb_type(opt)) {
    case MRB_TT_DATA: /* IO */
      return (int)mrb_fixnum(mrb_io_fileno(mrb, opt));
    case MRB_TT_FIXNUM:
      return (int)mrb_fixnum(opt);
    default:
      mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong exec redirect action");
      break;
  }
  return -1; /* never reached */
}