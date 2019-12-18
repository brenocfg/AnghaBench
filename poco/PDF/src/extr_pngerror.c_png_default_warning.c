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
typedef  int /*<<< orphan*/  png_structp ;
typedef  char* png_const_charp ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void /* PRIVATE */
png_default_warning(png_structp png_ptr, png_const_charp warning_message)
{
#ifndef PNG_NO_CONSOLE_IO
#  ifdef PNG_ERROR_NUMBERS_SUPPORTED
   if (*warning_message == '#')
   {
     int offset;
     char warning_number[16];
     for (offset=0; offset<15; offset++)
     {
        warning_number[offset]=*(warning_message+offset+1);
        if (*(warning_message+offset) == ' ')
            break;
     }
     if((offset > 1) && (offset < 15))
     {
       warning_number[offset-1]='\0';
       fprintf(stderr, "libpng warning no. %s: %s\n", warning_number,
          warning_message+offset);
     }
     else
       fprintf(stderr, "libpng warning: %s\n", warning_message);
   }
   else
#  endif
     fprintf(stderr, "libpng warning: %s\n", warning_message);
#else
   warning_message = warning_message; /* make compiler happy */
#endif
   png_ptr = png_ptr; /* make compiler happy */
}