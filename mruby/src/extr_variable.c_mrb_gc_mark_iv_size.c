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
struct RObject {int /*<<< orphan*/  iv; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 size_t iv_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
mrb_gc_mark_iv_size(mrb_state *mrb, struct RObject *obj)
{
  return iv_size(mrb, obj->iv);
}