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
struct d_info {int options; } ;

/* Variables and functions */
 int DMGL_PARAMS ; 
 scalar_t__ IS_DIGIT (char) ; 
 scalar_t__ IS_LOWER (char) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_clone_suffix (struct d_info*,struct demangle_component*) ; 
 struct demangle_component* d_encoding (struct d_info*,int) ; 
 char d_peek_char (struct d_info*) ; 
 char d_peek_next_char (struct d_info*) ; 

struct demangle_component *
cplus_demangle_mangled_name (struct d_info *di, int top_level)
{
  struct demangle_component *p;

  if (! d_check_char (di, '_')
      /* Allow missing _ if not at toplevel to work around a
	 bug in G++ abi-version=2 mangling; see the comment in
	 write_template_arg.  */
      && top_level)
    return NULL;
  if (! d_check_char (di, 'Z'))
    return NULL;
  p = d_encoding (di, top_level);

  /* If at top level and parsing parameters, check for a clone
     suffix.  */
  if (top_level && (di->options & DMGL_PARAMS) != 0)
    while (d_peek_char (di) == '.'
	   && (IS_LOWER (d_peek_next_char (di))
	       || d_peek_next_char (di) == '_'
	       || IS_DIGIT (d_peek_next_char (di))))
      p = d_clone_suffix (di, p);

  return p;
}