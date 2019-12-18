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
typedef  scalar_t__ pcre_uint32 ;

/* Variables and functions */
 unsigned int UCD_CASESET (scalar_t__) ; 
 scalar_t__ UCD_OTHERCASE (scalar_t__) ; 

__attribute__((used)) static int
get_othercase_range(pcre_uint32 *cptr, pcre_uint32 d, pcre_uint32 *ocptr,
  pcre_uint32 *odptr)
{
pcre_uint32 c, othercase, next;
unsigned int co;

/* Find the first character that has an other case. If it has multiple other
cases, return its case offset value. */

for (c = *cptr; c <= d; c++)
  {
  if ((co = UCD_CASESET(c)) != 0)
    {
    *ocptr = c++;   /* Character that has the set */
    *cptr = c;      /* Rest of input range */
    return (int)co;
    }
  if ((othercase = UCD_OTHERCASE(c)) != c) break;
  }

if (c > d) return -1;  /* Reached end of range */

/* Found a character that has a single other case. Search for the end of the
range, which is either the end of the input range, or a character that has zero
or more than one other cases. */

*ocptr = othercase;
next = othercase + 1;

for (++c; c <= d; c++)
  {
  if ((co = UCD_CASESET(c)) != 0 || UCD_OTHERCASE(c) != next) break;
  next++;
  }

*odptr = next - 1;     /* End of othercase range */
*cptr = c;             /* Rest of input range */
return 0;
}