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
 int /*<<< orphan*/  DEMANGLE_COMPONENT_FUNCTION_TYPE ; 
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,struct demangle_component*) ; 
 struct demangle_component* d_parmlist (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_bare_function_type (struct d_info *di, int has_return_type)
{
  struct demangle_component *return_type;
  struct demangle_component *tl;
  char peek;

  /* Detect special qualifier indicating that the first argument
     is the return type.  */
  peek = d_peek_char (di);
  if (peek == 'J')
    {
      d_advance (di, 1);
      has_return_type = 1;
    }

  if (has_return_type)
    {
      return_type = cplus_demangle_type (di);
      if (return_type == NULL)
	return NULL;
    }
  else
    return_type = NULL;

  tl = d_parmlist (di);
  if (tl == NULL)
    return NULL;

  return d_make_comp (di, DEMANGLE_COMPONENT_FUNCTION_TYPE,
		      return_type, tl);
}