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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  ISDIGIT (char const) ; 
 scalar_t__ mrb_ident_p (char const*,int) ; 

__attribute__((used)) static mrb_bool
cv_name_p(mrb_state *mrb, const char *name, mrb_int len)
{
  return len > 2 && name[0] == '@' && name[1] == '@' &&
         !ISDIGIT(name[2]) && mrb_ident_p(name+2, len-2);
}