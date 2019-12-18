#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct RString {int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_2__ {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 TYPE_1__* mrb_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
str_with_class(struct RString *s, mrb_value obj)
{
  s->c = mrb_str_ptr(obj)->c;
}