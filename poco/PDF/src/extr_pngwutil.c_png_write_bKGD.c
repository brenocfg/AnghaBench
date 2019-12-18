#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
typedef  int /*<<< orphan*/  png_size_t ;
typedef  TYPE_2__* png_color_16p ;
typedef  int png_byte ;
struct TYPE_8__ {scalar_t__ index; int red; int green; int blue; int gray; } ;
struct TYPE_7__ {scalar_t__ num_palette; int mng_features_permitted; int bit_depth; } ;

/* Variables and functions */
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int PNG_FLAG_MNG_EMPTY_PLTE ; 
 int /*<<< orphan*/  PNG_bKGD ; 
 int /*<<< orphan*/  png_bKGD ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_save_uint_16 (int*,int) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_write_chunk (TYPE_1__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_write_bKGD(png_structp png_ptr, png_color_16p back, int color_type)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_bKGD;
#endif
   png_byte buf[6];

   png_debug(1, "in png_write_bKGD\n");
   if (color_type == PNG_COLOR_TYPE_PALETTE)
   {
      if (
#if defined(PNG_MNG_FEATURES_SUPPORTED)
          (png_ptr->num_palette ||
          (!(png_ptr->mng_features_permitted & PNG_FLAG_MNG_EMPTY_PLTE))) &&
#endif
         back->index > png_ptr->num_palette)
      {
         png_warning(png_ptr, "Invalid background palette index");
         return;
      }
      buf[0] = back->index;
      png_write_chunk(png_ptr, png_bKGD, buf, (png_size_t)1);
   }
   else if (color_type & PNG_COLOR_MASK_COLOR)
   {
      png_save_uint_16(buf, back->red);
      png_save_uint_16(buf + 2, back->green);
      png_save_uint_16(buf + 4, back->blue);
      if(png_ptr->bit_depth == 8 && (buf[0] | buf[2] | buf[4]))
         {
            png_warning(png_ptr,
              "Ignoring attempt to write 16-bit bKGD chunk when bit_depth is 8");
            return;
         }
      png_write_chunk(png_ptr, png_bKGD, buf, (png_size_t)6);
   }
   else
   {
      if(back->gray >= (1 << png_ptr->bit_depth))
      {
         png_warning(png_ptr,
           "Ignoring attempt to write bKGD chunk out-of-range for bit_depth");
         return;
      }
      png_save_uint_16(buf, back->gray);
      png_write_chunk(png_ptr, png_bKGD, buf, (png_size_t)2);
   }
}