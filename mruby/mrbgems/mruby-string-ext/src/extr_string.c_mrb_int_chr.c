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
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_ASCII_8BIT ; 
 int /*<<< orphan*/  ENC_BINARY ; 
 scalar_t__ ENC_COMP_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENC_UTF8 ; 
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  int_chr_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_chr_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_int_chr(mrb_state *mrb, mrb_value num)
{
  mrb_value enc;
  mrb_bool enc_given;

  mrb_get_args(mrb, "|S?", &enc, &enc_given);
  if (!enc_given ||
      ENC_COMP_P(enc, ENC_ASCII_8BIT) ||
      ENC_COMP_P(enc, ENC_BINARY)) {
    return int_chr_binary(mrb, num);
  }
#ifdef MRB_UTF8_STRING
  else if (ENC_COMP_P(enc, ENC_UTF8)) {
    return int_chr_utf8(mrb, num);
  }
#endif
  else {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "unknown encoding name - %v", enc);
  }
  /* not reached */
  return mrb_nil_value();
}