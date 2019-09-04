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
struct d_growable_string {char* buf; int alc; scalar_t__ allocation_failure; } ;

/* Variables and functions */
 int /*<<< orphan*/  cplus_demangle_print_callback (int,struct demangle_component*,int /*<<< orphan*/ ,struct d_growable_string*) ; 
 int /*<<< orphan*/  d_growable_string_callback_adapter ; 
 int /*<<< orphan*/  d_growable_string_init (struct d_growable_string*,int) ; 
 int /*<<< orphan*/  free (char*) ; 

char *
cplus_demangle_print (int options, struct demangle_component *dc,
                      int estimate, size_t *palc)
{
  struct d_growable_string dgs;

  d_growable_string_init (&dgs, estimate);

  if (! cplus_demangle_print_callback (options, dc,
                                       d_growable_string_callback_adapter,
                                       &dgs))
    {
      free (dgs.buf);
      *palc = 0;
      return NULL;
    }

  *palc = dgs.allocation_failure ? 1 : dgs.alc;
  return dgs.buf;
}