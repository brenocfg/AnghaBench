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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_row_infop ;
struct TYPE_4__ {int transformations; int flags; scalar_t__ row_buf; int /*<<< orphan*/  shift; scalar_t__ bit_depth; int /*<<< orphan*/  (* write_user_transform_fn ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int PNG_BGR ; 
 int PNG_FILLER ; 
 int PNG_FLAG_FILLER_AFTER ; 
 int PNG_INVERT_ALPHA ; 
 int PNG_INVERT_MONO ; 
 int PNG_PACK ; 
 int PNG_PACKSWAP ; 
 int PNG_SHIFT ; 
 int PNG_SWAP_ALPHA ; 
 int PNG_SWAP_BYTES ; 
 int PNG_USER_TRANSFORM ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_do_bgr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_do_invert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_do_pack (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_do_packswap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_do_shift (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_strip_channel (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  png_do_swap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_do_write_invert_alpha (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_do_write_swap_alpha (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void /* PRIVATE */
png_do_write_transformations(png_structrp png_ptr, png_row_infop row_info)
{
   png_debug(1, "in png_do_write_transformations");

   if (png_ptr == NULL)
      return;

#ifdef PNG_WRITE_USER_TRANSFORM_SUPPORTED
   if ((png_ptr->transformations & PNG_USER_TRANSFORM) != 0)
      if (png_ptr->write_user_transform_fn != NULL)
         (*(png_ptr->write_user_transform_fn)) /* User write transform
                                                 function */
             (png_ptr,  /* png_ptr */
             row_info,  /* row_info: */
                /*  png_uint_32 width;       width of row */
                /*  size_t rowbytes;         number of bytes in row */
                /*  png_byte color_type;     color type of pixels */
                /*  png_byte bit_depth;      bit depth of samples */
                /*  png_byte channels;       number of channels (1-4) */
                /*  png_byte pixel_depth;    bits per pixel (depth*channels) */
             png_ptr->row_buf + 1);      /* start of pixel data for row */
#endif

#ifdef PNG_WRITE_FILLER_SUPPORTED
   if ((png_ptr->transformations & PNG_FILLER) != 0)
      png_do_strip_channel(row_info, png_ptr->row_buf + 1,
          !(png_ptr->flags & PNG_FLAG_FILLER_AFTER));
#endif

#ifdef PNG_WRITE_PACKSWAP_SUPPORTED
   if ((png_ptr->transformations & PNG_PACKSWAP) != 0)
      png_do_packswap(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_WRITE_PACK_SUPPORTED
   if ((png_ptr->transformations & PNG_PACK) != 0)
      png_do_pack(row_info, png_ptr->row_buf + 1,
          (png_uint_32)png_ptr->bit_depth);
#endif

#ifdef PNG_WRITE_SWAP_SUPPORTED
#  ifdef PNG_16BIT_SUPPORTED
   if ((png_ptr->transformations & PNG_SWAP_BYTES) != 0)
      png_do_swap(row_info, png_ptr->row_buf + 1);
#  endif
#endif

#ifdef PNG_WRITE_SHIFT_SUPPORTED
   if ((png_ptr->transformations & PNG_SHIFT) != 0)
      png_do_shift(row_info, png_ptr->row_buf + 1,
           &(png_ptr->shift));
#endif

#ifdef PNG_WRITE_SWAP_ALPHA_SUPPORTED
   if ((png_ptr->transformations & PNG_SWAP_ALPHA) != 0)
      png_do_write_swap_alpha(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_WRITE_INVERT_ALPHA_SUPPORTED
   if ((png_ptr->transformations & PNG_INVERT_ALPHA) != 0)
      png_do_write_invert_alpha(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_WRITE_BGR_SUPPORTED
   if ((png_ptr->transformations & PNG_BGR) != 0)
      png_do_bgr(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_WRITE_INVERT_SUPPORTED
   if ((png_ptr->transformations & PNG_INVERT_MONO) != 0)
      png_do_invert(row_info, png_ptr->row_buf + 1);
#endif
}