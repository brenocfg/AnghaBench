#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int caseset; scalar_t__ other_case; } ;
typedef  TYPE_1__ ucd_record ;
struct TYPE_6__ {int poptions; scalar_t__ start_subject; size_t end_subject; scalar_t__ partial; int /*<<< orphan*/  lcc; } ;
typedef  TYPE_2__ match_block ;
typedef  int /*<<< orphan*/  heapframe ;
typedef  size_t PCRE2_SPTR ;
typedef  size_t PCRE2_SIZE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CU2BYTES (size_t) ; 
 size_t Feptr ; 
 size_t Foffset_top ; 
 scalar_t__* Fovector ; 
 int /*<<< orphan*/  GETCHARINC (scalar_t__,size_t) ; 
 TYPE_1__* GET_UCD (scalar_t__) ; 
 int PCRE2_MATCH_UNSET_BACKREF ; 
 scalar_t__ PCRE2_UNSET ; 
 int PCRE2_UTF ; 
 scalar_t__* PRIV (int /*<<< orphan*/ ) ; 
 scalar_t__ TABLE_GET (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ UCHAR21INCTEST (size_t) ; 
 scalar_t__ UCHAR21TEST (size_t) ; 
 scalar_t__ memcmp (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucd_caseless_sets ; 

__attribute__((used)) static int
match_ref(PCRE2_SIZE offset, BOOL caseless, heapframe *F, match_block *mb,
  PCRE2_SIZE *lengthptr)
{
PCRE2_SPTR p;
PCRE2_SIZE length;
PCRE2_SPTR eptr;
PCRE2_SPTR eptr_start;

/* Deal with an unset group. The default is no match, but there is an option to
match an empty string. */

if (offset >= Foffset_top || Fovector[offset] == PCRE2_UNSET)
  {
  if ((mb->poptions & PCRE2_MATCH_UNSET_BACKREF) != 0)
    {
    *lengthptr = 0;
    return 0;      /* Match */
    }
  else return -1;  /* No match */
  }

/* Separate the caseless and UTF cases for speed. */

eptr = eptr_start = Feptr;
p = mb->start_subject + Fovector[offset];
length = Fovector[offset+1] - Fovector[offset];

if (caseless)
  {
#if defined SUPPORT_UNICODE
  if ((mb->poptions & PCRE2_UTF) != 0)
    {
    /* Match characters up to the end of the reference. NOTE: the number of
    code units matched may differ, because in UTF-8 there are some characters
    whose upper and lower case codes have different numbers of bytes. For
    example, U+023A (2 bytes in UTF-8) is the upper case version of U+2C65 (3
    bytes in UTF-8); a sequence of 3 of the former uses 6 bytes, as does a
    sequence of two of the latter. It is important, therefore, to check the
    length along the reference, not along the subject (earlier code did this
    wrong). */

    PCRE2_SPTR endptr = p + length;
    while (p < endptr)
      {
      uint32_t c, d;
      const ucd_record *ur;
      if (eptr >= mb->end_subject) return 1;   /* Partial match */
      GETCHARINC(c, eptr);
      GETCHARINC(d, p);
      ur = GET_UCD(d);
      if (c != d && c != (uint32_t)((int)d + ur->other_case))
        {
        const uint32_t *pp = PRIV(ucd_caseless_sets) + ur->caseset;
        for (;;)
          {
          if (c < *pp) return -1;  /* No match */
          if (c == *pp++) break;
          }
        }
      }
    }
  else
#endif

    /* Not in UTF mode */

    {
    for (; length > 0; length--)
      {
      uint32_t cc, cp;
      if (eptr >= mb->end_subject) return 1;   /* Partial match */
      cc = UCHAR21TEST(eptr);
      cp = UCHAR21TEST(p);
      if (TABLE_GET(cp, mb->lcc, cp) != TABLE_GET(cc, mb->lcc, cc))
        return -1;  /* No match */
      p++;
      eptr++;
      }
    }
  }

/* In the caseful case, we can just compare the code units, whether or not we
are in UTF mode. When partial matching, we have to do this unit-by-unit. */

else
  {
  if (mb->partial != 0)
    {
    for (; length > 0; length--)
      {
      if (eptr >= mb->end_subject) return 1;   /* Partial match */
      if (UCHAR21INCTEST(p) != UCHAR21INCTEST(eptr)) return -1;  /* No match */
      }
    }

  /* Not partial matching */

  else
    {
    if ((PCRE2_SIZE)(mb->end_subject - eptr) < length) return 1; /* Partial */
    if (memcmp(p, eptr, CU2BYTES(length)) != 0) return -1;  /* No match */
    eptr += length;
    }
  }

*lengthptr = eptr - eptr_start;
return 0;  /* Match */
}