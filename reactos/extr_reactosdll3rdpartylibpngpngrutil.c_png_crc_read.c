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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/ * png_structrp ;
typedef  int /*<<< orphan*/  png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  png_calculate_crc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_read_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
   if (png_ptr == NULL)
      return;

   png_read_data(png_ptr, buf, length);
   png_calculate_crc(png_ptr, buf, length);
}