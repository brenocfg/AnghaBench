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

/* Variables and functions */
 long last_immediate ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
format_dec (long number, char *outbuffer, int signedp)
{
  last_immediate = number;
  sprintf (outbuffer, signedp ? "%ld" : "%lu", number);

  return outbuffer + strlen (outbuffer);
}