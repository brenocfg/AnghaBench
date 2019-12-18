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
typedef  int /*<<< orphan*/ * png_bytep ;

/* Variables and functions */
 scalar_t__ isnonalpha (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_chunk_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_check_chunk_name(png_structp png_ptr, png_bytep chunk_name)
{
   png_debug(1, "in png_check_chunk_name\n");
   if (isnonalpha(chunk_name[0]) || isnonalpha(chunk_name[1]) ||
       isnonalpha(chunk_name[2]) || isnonalpha(chunk_name[3]))
   {
      png_chunk_error(png_ptr, "invalid chunk type");
   }
}