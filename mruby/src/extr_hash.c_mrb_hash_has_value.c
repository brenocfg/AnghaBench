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
struct has_v_arg {int /*<<< orphan*/  found; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RHASH_TBL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_has_value_i ; 
 int /*<<< orphan*/  ht_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct has_v_arg*) ; 
 int /*<<< orphan*/  mrb_bool_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
mrb_hash_has_value(mrb_state *mrb, mrb_value hash)
{
  mrb_value val;
  struct has_v_arg arg;
  
  mrb_get_args(mrb, "o", &val);
  arg.found = FALSE;
  arg.val = val;
  ht_foreach(mrb, RHASH_TBL(hash), hash_has_value_i, &arg);
  return mrb_bool_value(arg.found);
}