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
typedef  int /*<<< orphan*/  rand_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  get_opt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * random_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
random_m_rand(mrb_state *mrb, mrb_value self)
{
  mrb_value max;
  rand_state *t = random_ptr(self);

  max = get_opt(mrb);
  return random_rand(mrb, t, max);
}