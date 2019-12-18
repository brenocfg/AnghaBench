#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
typedef  scalar_t__ png_size_t ;
typedef  int png_byte ;
struct TYPE_4__ {size_t sig_bytes; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_HAVE_PNG_SIGNATURE ; 
 int /*<<< orphan*/  png_write_data (TYPE_1__*,int*,scalar_t__) ; 

void /* PRIVATE */
png_write_sig(png_structp png_ptr)
{
   png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
   /* write the rest of the 8 byte signature */
   png_write_data(png_ptr, &png_signature[png_ptr->sig_bytes],
      (png_size_t)8 - png_ptr->sig_bytes);
   if(png_ptr->sig_bytes < 3)
      png_ptr->mode |= PNG_HAVE_PNG_SIGNATURE;
}