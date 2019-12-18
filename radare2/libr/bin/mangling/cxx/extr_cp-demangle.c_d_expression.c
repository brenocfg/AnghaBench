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
struct demangle_component {int dummy; } ;
struct d_info {int is_expression; } ;

/* Variables and functions */
 struct demangle_component* d_expression_1 (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_expression (struct d_info *di)
{
  struct demangle_component *ret;
  int was_expression = di->is_expression;

  di->is_expression = 1;
  ret = d_expression_1 (di);
  di->is_expression = was_expression;
  return ret;
}