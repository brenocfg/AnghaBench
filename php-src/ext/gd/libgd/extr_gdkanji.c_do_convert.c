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
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EILSEQ ; 
 scalar_t__ EINVAL ; 
 unsigned char ESC ; 
 int /*<<< orphan*/  EUCSTR ; 
 int FALSE ; 
 int /*<<< orphan*/  NEWJISSTR ; 
 int /*<<< orphan*/  OLDJISSTR ; 
 int /*<<< orphan*/  SJISSTR ; 
 int /*<<< orphan*/  SJIStoJIS (int*,int*) ; 
 unsigned char SS2 ; 
 int TRUE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ iconv (int /*<<< orphan*/ ,char**,size_t*,char**,size_t*) ; 
 scalar_t__ iconv_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iconv_open (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  ustrcpy (unsigned char*,unsigned char*) ; 

__attribute__((used)) static void
do_convert (unsigned char *to, unsigned char *from, const char *code)
{
#ifdef HAVE_ICONV
  iconv_t cd;
  size_t from_len, to_len;

  if ((cd = iconv_open (EUCSTR, code)) == (iconv_t) - 1)
    {
      error ("iconv_open() error");
      if (errno == EINVAL)
	error ("invalid code specification: \"%s\" or \"%s\"",
	       EUCSTR, code);
      strcpy ((char *) to, (const char *) from);
      return;
    }

  from_len = strlen ((const char *) from) + 1;
  to_len = BUFSIZ;

  if ((int) iconv(cd, (char **) &from, &from_len, (char **) &to, &to_len) == -1)
    {
      if (errno == EINVAL)
	error ("invalid end of input string");
      else if (errno == EILSEQ)
	error ("invalid code in input string");
      else if (errno == E2BIG)
	error ("output buffer overflow at do_convert()");
      else
	error ("something happen");
      strcpy ((char *) to, (const char *) from);
      return;
    }

  if (iconv_close (cd) != 0)
    {
      error ("iconv_close() error");
    }
#else
  int p1, p2, i, j;
  int jisx0208 = FALSE;
  int hankaku = FALSE;

  j = 0;
  if (strcmp (code, NEWJISSTR) == 0 || strcmp (code, OLDJISSTR) == 0)
    {
      for (i = 0; from[i] != '\0' && j < BUFSIZ; i++)
	{
	  if (from[i] == ESC)
	    {
	      i++;
	      if (from[i] == '$')
		{
		  jisx0208 = TRUE;
		  hankaku = FALSE;
		  i++;
		}
	      else if (from[i] == '(')
		{
		  jisx0208 = FALSE;
		  i++;
		  if (from[i] == 'I')	/* Hankaku Kana */
		    hankaku = TRUE;
		  else
		    hankaku = FALSE;
		}
	    }
	  else
	    {
	      if (jisx0208)
		to[j++] = from[i] + 128;
	      else if (hankaku)
		{
		  to[j++] = SS2;
		  to[j++] = from[i] + 128;
		}
	      else
		to[j++] = from[i];
	    }
	}
    }
  else if (strcmp (code, SJISSTR) == 0)
    {
      for (i = 0; from[i] != '\0' && j < BUFSIZ; i++)
	{
	  p1 = from[i];
	  if (p1 < 127)
	    to[j++] = p1;
	  else if ((p1 >= 161) && (p1 <= 223))
	    {			/* Hankaku Kana */
	      to[j++] = SS2;
	      to[j++] = p1;
	    }
	  else
	    {
	      p2 = from[++i];
	      SJIStoJIS (&p1, &p2);
	      to[j++] = p1 + 128;
	      to[j++] = p2 + 128;
	    }
	}
    }
  else
    {
      error ("invalid code specification: \"%s\"", code);
      return;
    }

  if (j >= BUFSIZ)
    {
      error ("output buffer overflow at do_convert()");
      ustrcpy (to, from);
    }
  else
    to[j] = '\0';
#endif /* HAVE_ICONV */
}