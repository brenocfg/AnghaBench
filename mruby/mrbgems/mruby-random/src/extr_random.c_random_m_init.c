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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  rand_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  get_opt (int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * random_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
random_m_init(mrb_state *mrb, mrb_value self)
{
  mrb_value seed;
  rand_state *t;

  seed = get_opt(mrb);
  /* avoid memory leaks */
  t = random_ptr(self);
  if (mrb_nil_p(seed)) {
    rand_init(t);
  }
  else {
    rand_seed(t, (uint32_t)mrb_fixnum(seed));
  }

  return self;
}