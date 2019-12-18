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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  rand_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  get_opt (int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 scalar_t__ rand_seed (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rand_uint32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * random_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
random_m_srand(mrb_state *mrb, mrb_value self)
{
  uint32_t seed;
  uint32_t old_seed;
  mrb_value sv;
  rand_state *t = random_ptr(self);

  sv = get_opt(mrb);
  if (mrb_nil_p(sv)) {
    seed = (uint32_t)time(NULL) + rand_uint32(t);
  }
  else {
    seed = (uint32_t)mrb_fixnum(sv);
  }
  old_seed = rand_seed(t, seed);

  return mrb_fixnum_value((mrb_int)old_seed);
}