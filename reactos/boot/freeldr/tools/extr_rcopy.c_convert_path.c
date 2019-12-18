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
 char* strdup (char*) ; 

char* convert_path(char* origpath)
{
   char* newpath;
   int i;

   newpath = strdup(origpath);

   i = 0;
   while (newpath[i] != 0)
     {
#ifdef UNIX_PATHS
    if (newpath[i] == '\\')
      {
         newpath[i] = '/';
      }
#else
#ifdef DOS_PATHS
    if (newpath[i] == '/')
      {
         newpath[i] = '\\';
      }
#endif
#endif
    i++;
     }
   return(newpath);
}