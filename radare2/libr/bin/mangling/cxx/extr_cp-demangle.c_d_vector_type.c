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
 int /*<<< orphan*/  DEMANGLE_COMPONENT_VECTOR_TYPE ; 
 int /*<<< orphan*/  cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_expression (struct d_info*) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,int /*<<< orphan*/ ) ; 
 struct demangle_component* d_number_component (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_vector_type (struct d_info *di)
{
  char peek;
  struct demangle_component *dim;

  peek = d_peek_char (di);
  if (peek == '_')
    {
      d_advance (di, 1);
      dim = d_expression (di);
    }
  else
    dim = d_number_component (di);

  if (dim == NULL)
    return NULL;

  if (! d_check_char (di, '_'))
    return NULL;

  return d_make_comp (di, DEMANGLE_COMPONENT_VECTOR_TYPE, dim,
		      cplus_demangle_type (di));
}