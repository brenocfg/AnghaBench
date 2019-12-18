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
typedef  TYPE_1__* png_structp ;
struct TYPE_4__ {int transformations; scalar_t__ row_buf; int /*<<< orphan*/  row_info; int /*<<< orphan*/  shift; scalar_t__ bit_depth; int /*<<< orphan*/  flags; int /*<<< orphan*/  (* write_user_transform_fn ) (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int PNG_BGR ; 
 int PNG_FILLER ; 
 int PNG_INVERT_ALPHA ; 
 int PNG_INVERT_MONO ; 
 int PNG_PACK ; 
 int PNG_PACKSWAP ; 
 int PNG_SHIFT ; 
 int PNG_SWAP_ALPHA ; 
 int PNG_SWAP_BYTES ; 
 int PNG_USER_TRANSFORM ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_do_bgr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_do_invert (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_do_pack (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_do_packswap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_do_shift (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_strip_filler (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_do_swap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_do_write_invert_alpha (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_do_write_swap_alpha (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

void /* PRIVATE */
png_do_write_transformations(png_structp png_ptr)
{
   png_debug(1, "in png_do_write_transformations\n");

   if (png_ptr == NULL)
      return;

#if defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED)
   if (png_ptr->transformations & PNG_USER_TRANSFORM)
      if(png_ptr->write_user_transform_fn != NULL)
        (*(png_ptr->write_user_transform_fn)) /* user write transform function */
          (png_ptr,                    /* png_ptr */
           &(png_ptr->row_info),       /* row_info:     */
             /*  png_uint_32 width;          width of row */
             /*  png_uint_32 rowbytes;       number of bytes in row */
             /*  png_byte color_type;        color type of pixels */
             /*  png_byte bit_depth;         bit depth of samples */
             /*  png_byte channels;          number of channels (1-4) */
             /*  png_byte pixel_depth;       bits per pixel (depth*channels) */
           png_ptr->row_buf + 1);      /* start of pixel data for row */
#endif
#if defined(PNG_WRITE_FILLER_SUPPORTED)
   if (png_ptr->transformations & PNG_FILLER)
      png_do_strip_filler(&(png_ptr->row_info), png_ptr->row_buf + 1,
         png_ptr->flags);
#endif
#if defined(PNG_WRITE_PACKSWAP_SUPPORTED)
   if (png_ptr->transformations & PNG_PACKSWAP)
      png_do_packswap(&(png_ptr->row_info), png_ptr->row_buf + 1);
#endif
#if defined(PNG_WRITE_PACK_SUPPORTED)
   if (png_ptr->transformations & PNG_PACK)
      png_do_pack(&(png_ptr->row_info), png_ptr->row_buf + 1,
         (png_uint_32)png_ptr->bit_depth);
#endif
#if defined(PNG_WRITE_SWAP_SUPPORTED)
   if (png_ptr->transformations & PNG_SWAP_BYTES)
      png_do_swap(&(png_ptr->row_info), png_ptr->row_buf + 1);
#endif
#if defined(PNG_WRITE_SHIFT_SUPPORTED)
   if (png_ptr->transformations & PNG_SHIFT)
      png_do_shift(&(png_ptr->row_info), png_ptr->row_buf + 1,
         &(png_ptr->shift));
#endif
#if defined(PNG_WRITE_SWAP_ALPHA_SUPPORTED)
   if (png_ptr->transformations & PNG_SWAP_ALPHA)
      png_do_write_swap_alpha(&(png_ptr->row_info), png_ptr->row_buf + 1);
#endif
#if defined(PNG_WRITE_INVERT_ALPHA_SUPPORTED)
   if (png_ptr->transformations & PNG_INVERT_ALPHA)
      png_do_write_invert_alpha(&(png_ptr->row_info), png_ptr->row_buf + 1);
#endif
#if defined(PNG_WRITE_BGR_SUPPORTED)
   if (png_ptr->transformations & PNG_BGR)
      png_do_bgr(&(png_ptr->row_info), png_ptr->row_buf + 1);
#endif
#if defined(PNG_WRITE_INVERT_SUPPORTED)
   if (png_ptr->transformations & PNG_INVERT_MONO)
      png_do_invert(&(png_ptr->row_info), png_ptr->row_buf + 1);
#endif
}