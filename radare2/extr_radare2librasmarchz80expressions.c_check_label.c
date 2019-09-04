#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct label {char* name; TYPE_2__* ref; struct label* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  done; } ;
struct TYPE_3__ {int line; } ;

/* Variables and functions */
 int addr ; 
 int /*<<< orphan*/  compute_ref (TYPE_2__*,int) ; 
 char* delspc (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 scalar_t__ isalnum (unsigned char const) ; 
 size_t sp ; 
 TYPE_1__* stack ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int strlen (char*) ; 
 int strncmp (char*,char const*,unsigned int) ; 
 int verbose ; 

__attribute__((used)) static int
check_label (struct label *labels, const char **p, struct label **ret,
	     struct label **previous, int force_skip)
{
  struct label *l;
  const char *c;
  unsigned s2;
  *p = delspc (*p);
  for (c = *p; isalnum ((const unsigned char)*c) || *c == '_' || *c == '.'; ++c)
    {
    }
  s2 = c - *p;
  for (l = labels; l; l = l->next)
    {
      unsigned s1, s;
      int cmp;
      s1 = strlen (l->name);
      s = s1 < s2 ? s1 : s2;
      cmp = strncmp (l->name, *p, s);
      if (cmp > 0 || (cmp == 0 && s1 > s))
	{
	  if (force_skip)
	    *p = c;
	  return 0;
	}
      if (cmp < 0 || s2 > s)
	{
	  if (previous)
	    *previous = l;
	  continue;
	}
      *p = c;
      /* if label is not valid, compute it */
      if (l->ref)
	{
	  compute_ref (l->ref, 1);
	  if (!l->ref->done)
	    {
	      /* label was not valid, and isn't computable.  tell the
	       * caller that it doesn't exist, so it will try again later.
	       * Set ret to show actual existence.  */
	      if (verbose >= 6)
		fprintf (stderr,
			 "%5d (0x%04x): returning invalid label %s.\n",
			 stack[sp].line, addr, l->name);
	      *ret = l;
	      return 0;
	    }
	}
      *ret = l;
      return 1;
    }
  if (force_skip)
    *p = c;
  return 0;
}