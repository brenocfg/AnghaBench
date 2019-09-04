#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct label {int value; } ;
struct TYPE_2__ {int line; int /*<<< orphan*/  labels; } ;

/* Variables and functions */
 int addr ; 
 scalar_t__ check_label (int /*<<< orphan*/ ,char const**,struct label**,struct label**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printerr (int,char*,int,char const*) ; 
 size_t sp ; 
 TYPE_1__* stack ; 
 int /*<<< orphan*/  stderr ; 
 int verbose ; 

__attribute__((used)) static int
rd_label (const char **p, int *exists, struct label **previous, int level,
	  int print_errors)
{
  struct label *l = NULL;
  int s;
  if (exists)
    *exists = 0;
  if (previous)
    *previous = NULL;
  if (verbose >= 6)
    fprintf (stderr, "%5d (0x%04x): Starting to read label (string=%s).\n",
	     stack[sp].line, addr, *p);
  for (s = level; s >= 0; --s)
    {
      if (check_label (stack[s].labels, p, &l,
		       (**p == '.' && s == sp) ? previous : NULL, 0))
	break;
    }
  if (s < 0)
    {
      /* not yet found */
      const char *old_p = *p;
	  /* label does not exist, or is invalid.  This is an error if there
	   * is no existence check.  */
	  if (!exists && print_errors)
	    printerr (1, "using undefined label %.*s\n", *p - old_p, old_p);
	  /* Return a value to discriminate between non-existing and invalid */
	  if (verbose >= 7)
	    fprintf (stderr, "rd_label returns invalid value\n");
	  return l != NULL;
    }
  if (exists)
    *exists = 1;
  if (verbose >= 7)
    fprintf (stderr, "rd_label returns valid value 0x%x\n", l->value);
  return l->value;
}