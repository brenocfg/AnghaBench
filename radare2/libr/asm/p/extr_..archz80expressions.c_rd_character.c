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
struct TYPE_2__ {int line; } ;

/* Variables and functions */
 int addr ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  printerr (int,char*) ; 
 size_t sp ; 
 TYPE_1__* stack ; 
 int /*<<< orphan*/  stderr ; 
 int verbose ; 

__attribute__((used)) static int
rd_character (const char **p, int *valid, int print_errors)
{
  int i;
  if (verbose >= 6)
    fprintf (stderr,
	     "%5d (0x%04x): Starting to read character (string=%s).\n",
	     stack[sp].line, addr, *p);
  i = **p;
  if (!i)
    {
      if (valid)
	*valid = 0;
      else if (print_errors)
	printerr (1, "unexpected end of line in string constant\n");
      return 0;
    }
  if (i == '\\')
    {
      (*p)++;
      if (**p >= '0' && **p <= '7')
	{
	  int b, num_digits;
	  i = 0;
	  if ((*p)[1] >= '0' && (*p)[1] <= '7')
	    {
	      if (**p <= '3' && (*p)[2] >= '0' && (*p)[2] <= '7')
		num_digits = 3;
	      else
		num_digits = 2;
	    }
	  else
	    num_digits = 1;
	  for (b = 0; b < num_digits; ++b)
	    {
	      int bit = (*p)[num_digits - 1 - b] - '0';
	      i += (1 << (b * 3)) * bit;
	    }
	  *p += num_digits;
	}
      else
	{
	  switch (**p)
	    {
	    case 'n':
	      i = 10;
	      break;
	    case 'r':
	      i = 13;
	      break;
	    case 't':
	      i = 9;
	      break;
	    case 'a':
	      i = 7;
	      break;
	    case '\'':
	      if (valid)
		*valid = 0;
	      else if (print_errors)
		printerr (1, "empty literal character\n");
	      return 0;
	    case 0:
	      if (valid)
		*valid = 0;
	      else if (print_errors)
		printerr (1, "unexpected end of line after "
			  "backslash in string constant\n");
	      return 0;
	    default:
	      i = **p;
	    }
	  (*p)++;
	}
    }
  else
    (*p)++;
  if (verbose >= 7)
    fprintf (stderr, "%5d (0x%04x): rd_character returned %d (%c).\n",
	     stack[sp].line, addr, i, i);
  return i;
}