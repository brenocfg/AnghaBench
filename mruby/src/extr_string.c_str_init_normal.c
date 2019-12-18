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
struct RString {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct RString* str_init_normal_capa (int /*<<< orphan*/ *,struct RString*,char const*,size_t,size_t) ; 

__attribute__((used)) static struct RString*
str_init_normal(mrb_state *mrb, struct RString *s, const char *p, size_t len)
{
  return str_init_normal_capa(mrb, s, p, len, len);
}