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
typedef  enum demangle_component_type { ____Placeholder_demangle_component_type } demangle_component_type ;

/* Variables and functions */
 int DEMANGLE_COMPONENT_QUAL_NAME ; 
 int DEMANGLE_COMPONENT_TEMPLATE ; 
 scalar_t__ IS_DIGIT (char) ; 
 scalar_t__ IS_LOWER (char) ; 
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_add_substitution (struct d_info*,struct demangle_component*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 struct demangle_component* d_make_comp (struct d_info*,int,struct demangle_component*,struct demangle_component*) ; 
 char d_peek_char (struct d_info*) ; 
 char d_peek_next_char (struct d_info*) ; 
 struct demangle_component* d_substitution (struct d_info*,int) ; 
 struct demangle_component* d_template_args (struct d_info*) ; 
 struct demangle_component* d_template_param (struct d_info*) ; 
 struct demangle_component* d_unqualified_name (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_prefix (struct d_info *di)
{
  struct demangle_component *ret = NULL;

  while (1)
    {
      char peek;
      enum demangle_component_type comb_type;
      struct demangle_component *dc;

      peek = d_peek_char (di);
      if (peek == '\0')
	return NULL;

      /* The older code accepts a <local-name> here, but I don't see
	 that in the grammar.  The older code does not accept a
	 <template-param> here.  */

      comb_type = DEMANGLE_COMPONENT_QUAL_NAME;
      if (peek == 'D')
	{
	  char peek2 = d_peek_next_char (di);
	  if (peek2 == 'T' || peek2 == 't')
	    /* Decltype.  */
	    dc = cplus_demangle_type (di);
	  else
	    /* Destructor name.  */
	    dc = d_unqualified_name (di);
	}
      else if (IS_DIGIT (peek)
	  || IS_LOWER (peek)
	  || peek == 'C'
	  || peek == 'U'
	  || peek == 'L')
	dc = d_unqualified_name (di);
      else if (peek == 'S')
	dc = d_substitution (di, 1);
      else if (peek == 'I')
	{
	  if (ret == NULL)
	    return NULL;
	  comb_type = DEMANGLE_COMPONENT_TEMPLATE;
	  dc = d_template_args (di);
	}
      else if (peek == 'T')
	dc = d_template_param (di);
      else if (peek == 'E')
	return ret;
      else if (peek == 'M')
	{
	  /* Initializer scope for a lambda.  We don't need to represent
	     this; the normal code will just treat the variable as a type
	     scope, which gives appropriate output.  */
	  if (ret == NULL)
	    return NULL;
	  d_advance (di, 1);
	  continue;
	}
      else
	return NULL;

      if (ret == NULL)
	ret = dc;
      else
	ret = d_make_comp (di, comb_type, ret, dc);

      if (peek != 'S' && d_peek_char (di) != 'E')
	{
	  if (! d_add_substitution (di, ret))
	    return NULL;
	}
    }
}