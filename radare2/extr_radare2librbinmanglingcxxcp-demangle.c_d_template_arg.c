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
struct d_info {int dummy; } ;

/* Variables and functions */
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_expr_primary (struct d_info*) ; 
 struct demangle_component* d_expression (struct d_info*) ; 
 int d_peek_char (struct d_info*) ; 
 struct demangle_component* d_template_args (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_template_arg (struct d_info *di)
{
  struct demangle_component *ret;

  switch (d_peek_char (di))
    {
    case 'X':
      d_advance (di, 1);
      ret = d_expression (di);
      if (! d_check_char (di, 'E'))
	return NULL;
      return ret;

    case 'L':
      return d_expr_primary (di);

    case 'I':
    case 'J':
      /* An argument pack.  */
      return d_template_args (di);

    default:
      return cplus_demangle_type (di);
    }
}