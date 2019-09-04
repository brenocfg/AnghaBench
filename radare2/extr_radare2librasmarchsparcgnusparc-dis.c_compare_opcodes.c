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
struct TYPE_2__ {unsigned long match; unsigned long lose; int architecture; char* name; int flags; int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ sparc_opcode ;

/* Variables and functions */
 int F_ALIAS ; 
 char* _ (char*) ; 
 int current_arch_mask ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 unsigned int strcmp (char*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
compare_opcodes (const void * a, const void * b)
{
  sparc_opcode *op0 = * (sparc_opcode **) a;
  sparc_opcode *op1 = * (sparc_opcode **) b;
  unsigned long int match0 = op0->match, match1 = op1->match;
  unsigned long int lose0 = op0->lose, lose1 = op1->lose;
  register unsigned int i;

  /* If one (and only one) insn isn't supported by the current architecture,
     prefer the one that is.  If neither are supported, but they're both for
     the same architecture, continue processing.  Otherwise (both unsupported
     and for different architectures), prefer lower numbered arch's (fudged
     by comparing the bitmasks).  */
  if (op0->architecture & current_arch_mask)
    {
	  if (!(op1->architecture & current_arch_mask)) {
		  return -1;
	  }
    }
  else
    {
	    if (op1->architecture & current_arch_mask) {
		    return 1;
	    } else if (op0->architecture != op1->architecture) {
		    return op0->architecture - op1->architecture;
	    }
    }

  /* If a bit is set in both match and lose, there is something
     wrong with the opcode table.  */
  if (match0 & lose0)
    {
      fprintf
	(stderr,
	 /* xgettext:c-format */
	 _("Internal error:  bad sparc-opcode.h: \"%s\", %#.8lx, %#.8lx\n"),
	 op0->name, match0, lose0);
      op0->lose &= ~op0->match;
      lose0 = op0->lose;
    }

  if (match1 & lose1)
    {
      fprintf
	(stderr,
	 /* xgettext:c-format */
	 _("Internal error: bad sparc-opcode.h: \"%s\", %#.8lx, %#.8lx\n"),
	 op1->name, match1, lose1);
      op1->lose &= ~op1->match;
      lose1 = op1->lose;
    }

  /* Because the bits that are variable in one opcode are constant in
     another, it is important to order the opcodes in the right order.  */
  for (i = 0; i < 32; ++i)
    {
      unsigned long int x = 1 << i;
      int x0 = (match0 & x) != 0;
      int x1 = (match1 & x) != 0;

      if (x0 != x1) {
	      return x1 - x0;
      }
    }

  for (i = 0; i < 32; ++i)
    {
      unsigned long int x = 1 << i;
      int x0 = (lose0 & x) != 0;
      int x1 = (lose1 & x) != 0;

      if (x0 != x1) {
	      return x1 - x0;
      }
    }

  /* They are functionally equal.  So as long as the opcode table is
     valid, we can put whichever one first we want, on aesthetic grounds.  */

  /* Our first aesthetic ground is that aliases defer to real insns.  */
  {
    int alias_diff = (op0->flags & F_ALIAS) - (op1->flags & F_ALIAS);

    if (alias_diff != 0) {
	    /* Put the one that isn't an alias first.  */
	    return alias_diff;
    }
  }

  /* Except for aliases, two "identical" instructions had
     better have the same opcode.  This is a sanity check on the table.  */
  i = strcmp (op0->name, op1->name);
  if (i)
    {
	  if (op0->flags & F_ALIAS) { /* If they're both aliases, be arbitrary.  */
		  return i;
	  } else {
		  fprintf (stderr,
			  /* xgettext:c-format */
			  _ ("Internal error: bad sparc-opcode.h: \"%s\" == \"%s\"\n"),
			  op0->name, op1->name);
	  }
    }

  /* Fewer arguments are preferred.  */
  {
    int length_diff = strlen (op0->args) - strlen (op1->args);

    if (length_diff != 0) {
	    /* Put the one with fewer arguments first.  */
	    return length_diff;
    }
  }

  /* Put 1+i before i+1.  */
  {
    char *p0 = (char *) strchr (op0->args, '+');
    char *p1 = (char *) strchr (op1->args, '+');

    if (p0 && p1)
      {
	/* There is a plus in both operands.  Note that a plus
	   sign cannot be the first character in args,
	   so the following [-1]'s are valid.  */
	if (p0[-1] == 'i' && p1[1] == 'i') {
		/* op0 is i+1 and op1 is 1+i, so op1 goes first.  */
		return 1;
	}
	if (p0[1] == 'i' && p1[-1] == 'i') {
		/* op0 is 1+i and op1 is i+1, so op0 goes first.  */
		return -1;
	}
      }
  }

  /* Put 1,i before i,1.  */
  {
    int i0 = strncmp (op0->args, "i,1", 3) == 0;
    int i1 = strncmp (op1->args, "i,1", 3) == 0;

    if (i0 ^ i1) {
	    return i0 - i1;
    }
  }

  /* They are, as far as we can tell, identical.
     Since qsort may have rearranged the table partially, there is
     no way to tell which one was first in the opcode table as
     written, so just say there are equal.  */
  /* ??? This is no longer true now that we sort a vector of pointers,
     not the table itself.  */
  return 0;
}