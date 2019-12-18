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
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char const* strrchr (char const*,char) ; 

void
getFilename (const char *filename, char * fileSpec)
{
  if (strrchr (filename, '/') != 0)
  {
    strcpy (fileSpec, strrchr (filename, '/') + 1);
  }
  else
  {
    strcpy (fileSpec, filename);
  }
}