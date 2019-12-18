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
typedef  int /*<<< orphan*/  separators ;

/* Variables and functions */
 scalar_t__ SEP_TEST ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

char *
gd_strtok_r (char *s, char *sep, char **state)
{
  char separators[256];
  char *result = 0;
  memset (separators, 0, sizeof (separators));
  while (*sep)
    {
      separators[*((unsigned char *) sep)] = 1;
      sep++;
    }
  if (!s)
    {
      /* Pick up where we left off */
      s = *state;
    }
  /* 1. EOS */
  if (!(*s))
    {
      *state = s;
      return 0;
    }
  /* 2. Leading separators, if any */
  if (SEP_TEST)
    {
      do
	{
	  s++;
	}
      while (SEP_TEST);
      /* 2a. EOS after separators only */
      if (!(*s))
	{
	  *state = s;
	  return 0;
	}
    }
  /* 3. A token */
  result = s;
  do
    {
      /* 3a. Token at end of string */
      if (!(*s))
	{
	  *state = s;
	  return result;
	}
      s++;
    }
  while (!SEP_TEST);
  /* 4. Terminate token and skip trailing separators */
  *s = '\0';
  do
    {
      s++;
    }
  while (SEP_TEST);
  /* 5. Return token */
  *state = s;
  return result;
}