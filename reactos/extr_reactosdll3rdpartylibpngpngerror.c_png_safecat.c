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
typedef  char* png_const_charp ;
typedef  char* png_charp ;

/* Variables and functions */

size_t
png_safecat(png_charp buffer, size_t bufsize, size_t pos,
    png_const_charp string)
{
   if (buffer != NULL && pos < bufsize)
   {
      if (string != NULL)
         while (*string != '\0' && pos < bufsize-1)
           buffer[pos++] = *string++;

      buffer[pos] = '\0';
   }

   return pos;
}