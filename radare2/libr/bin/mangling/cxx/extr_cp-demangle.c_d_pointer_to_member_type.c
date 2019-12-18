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
 int /*<<< orphan*/  DEMANGLE_COMPONENT_PTRMEM_TYPE ; 
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,struct demangle_component*) ; 

__attribute__((used)) static struct demangle_component *
d_pointer_to_member_type (struct d_info *di)
{
  struct demangle_component *cl;
  struct demangle_component *mem;

  if (! d_check_char (di, 'M'))
    return NULL;

  cl = cplus_demangle_type (di);
  if (cl == NULL)
    return NULL;

  /* The ABI says, "The type of a non-static member function is considered
     to be different, for the purposes of substitution, from the type of a
     namespace-scope or static member function whose type appears
     similar. The types of two non-static member functions are considered
     to be different, for the purposes of substitution, if the functions
     are members of different classes. In other words, for the purposes of
     substitution, the class of which the function is a member is
     considered part of the type of function."

     For a pointer to member function, this call to cplus_demangle_type
     will end up adding a (possibly qualified) non-member function type to
     the substitution table, which is not correct; however, the member
     function type will never be used in a substitution, so putting the
     wrong type in the substitution table is harmless.  */

  mem = cplus_demangle_type (di);
  if (mem == NULL)
    return NULL;

  return d_make_comp (di, DEMANGLE_COMPONENT_PTRMEM_TYPE, cl, mem);
}