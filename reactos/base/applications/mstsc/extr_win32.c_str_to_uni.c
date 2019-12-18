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
typedef  char TCHAR ;

/* Variables and functions */
 int strlen (char*) ; 

__attribute__((used)) static void
str_to_uni(TCHAR * sizex, char * size1)
{
  int len;
  int i;

  len = strlen(size1);
  for (i = 0; i < len; i++)
  {
    sizex[i] = size1[i];
  }
  sizex[len] = 0;
}