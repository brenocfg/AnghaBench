#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
typedef  TYPE_2__* png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_35__ {int /*<<< orphan*/  next_out; scalar_t__ avail_out; } ;
struct TYPE_36__ {int mode; int buffer_size; scalar_t__ push_length; scalar_t__ color_type; scalar_t__ idat_size; int /*<<< orphan*/  chunk_name; int /*<<< orphan*/  row_buf; TYPE_1__ zstream; scalar_t__ irowbytes; int /*<<< orphan*/  process_mode; } ;
typedef  int /*<<< orphan*/  PNG_CONST ;

/* Variables and functions */
 int PNG_AFTER_IDAT ; 
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 int PNG_HAVE_CHUNK_AFTER_IDAT ; 
 int PNG_HAVE_CHUNK_HEADER ; 
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int /*<<< orphan*/  PNG_READ_DONE_MODE ; 
 int /*<<< orphan*/  PNG_READ_IDAT_MODE ; 
 int /*<<< orphan*/  png_IDAT ; 
 int /*<<< orphan*/  png_IEND ; 
 int /*<<< orphan*/  png_IHDR ; 
 int /*<<< orphan*/  png_PLTE ; 
 int /*<<< orphan*/  png_bKGD ; 
 int /*<<< orphan*/  png_cHRM ; 
 int /*<<< orphan*/  png_crc_read (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_gAMA ; 
 scalar_t__ png_get_uint_31 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_hIST ; 
 int /*<<< orphan*/  png_handle_IEND (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_IHDR (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_PLTE (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ png_handle_as_unknown (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_handle_bKGD (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_cHRM (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_gAMA (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_hIST (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_iCCP (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_oFFs (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_pCAL (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_pHYs (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_sBIT (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_sCAL (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_sPLT (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_sRGB (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_tIME (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_tRNS (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_handle_unknown (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_iCCP ; 
 int /*<<< orphan*/  png_iTXt ; 
 int /*<<< orphan*/  png_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_oFFs ; 
 int /*<<< orphan*/  png_pCAL ; 
 int /*<<< orphan*/  png_pHYs ; 
 int /*<<< orphan*/  png_push_fill_buffer (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_push_handle_iTXt (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_push_handle_tEXt (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_push_handle_unknown (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_push_handle_zTXt (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_push_have_end (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_push_have_info (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_push_save_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  png_reset_crc (TYPE_2__*) ; 
 int /*<<< orphan*/  png_sBIT ; 
 int /*<<< orphan*/  png_sCAL ; 
 int /*<<< orphan*/  png_sPLT ; 
 int /*<<< orphan*/  png_sRGB ; 
 int /*<<< orphan*/  png_tEXt ; 
 int /*<<< orphan*/  png_tIME ; 
 int /*<<< orphan*/  png_tRNS ; 
 int /*<<< orphan*/  png_zTXt ; 

void /* PRIVATE */
png_push_read_chunk(png_structp png_ptr, png_infop info_ptr)
{
#ifdef PNG_USE_LOCAL_ARRAYS
      PNG_CONST PNG_IHDR;
      PNG_CONST PNG_IDAT;
      PNG_CONST PNG_IEND;
      PNG_CONST PNG_PLTE;
#if defined(PNG_READ_bKGD_SUPPORTED)
      PNG_CONST PNG_bKGD;
#endif
#if defined(PNG_READ_cHRM_SUPPORTED)
      PNG_CONST PNG_cHRM;
#endif
#if defined(PNG_READ_gAMA_SUPPORTED)
      PNG_CONST PNG_gAMA;
#endif
#if defined(PNG_READ_hIST_SUPPORTED)
      PNG_CONST PNG_hIST;
#endif
#if defined(PNG_READ_iCCP_SUPPORTED)
      PNG_CONST PNG_iCCP;
#endif
#if defined(PNG_READ_iTXt_SUPPORTED)
      PNG_CONST PNG_iTXt;
#endif
#if defined(PNG_READ_oFFs_SUPPORTED)
      PNG_CONST PNG_oFFs;
#endif
#if defined(PNG_READ_pCAL_SUPPORTED)
      PNG_CONST PNG_pCAL;
#endif
#if defined(PNG_READ_pHYs_SUPPORTED)
      PNG_CONST PNG_pHYs;
#endif
#if defined(PNG_READ_sBIT_SUPPORTED)
      PNG_CONST PNG_sBIT;
#endif
#if defined(PNG_READ_sCAL_SUPPORTED)
      PNG_CONST PNG_sCAL;
#endif
#if defined(PNG_READ_sRGB_SUPPORTED)
      PNG_CONST PNG_sRGB;
#endif
#if defined(PNG_READ_sPLT_SUPPORTED)
      PNG_CONST PNG_sPLT;
#endif
#if defined(PNG_READ_tEXt_SUPPORTED)
      PNG_CONST PNG_tEXt;
#endif
#if defined(PNG_READ_tIME_SUPPORTED)
      PNG_CONST PNG_tIME;
#endif
#if defined(PNG_READ_tRNS_SUPPORTED)
      PNG_CONST PNG_tRNS;
#endif
#if defined(PNG_READ_zTXt_SUPPORTED)
      PNG_CONST PNG_zTXt;
#endif
#endif /* PNG_USE_LOCAL_ARRAYS */
   /* First we make sure we have enough data for the 4 byte chunk name
    * and the 4 byte chunk length before proceeding with decoding the
    * chunk data.  To fully decode each of these chunks, we also make
    * sure we have enough data in the buffer for the 4 byte CRC at the
    * end of every chunk (except IDAT, which is handled separately).
    */
   if (!(png_ptr->mode & PNG_HAVE_CHUNK_HEADER))
   {
      png_byte chunk_length[4];

      if (png_ptr->buffer_size < 8)
      {
         png_push_save_buffer(png_ptr);
         return;
      }

      png_push_fill_buffer(png_ptr, chunk_length, 4);
      png_ptr->push_length = png_get_uint_31(png_ptr,chunk_length);
      png_reset_crc(png_ptr);
      png_crc_read(png_ptr, png_ptr->chunk_name, 4);
      png_ptr->mode |= PNG_HAVE_CHUNK_HEADER;
   }

   if (!png_memcmp(png_ptr->chunk_name, png_IDAT, 4))
     if(png_ptr->mode & PNG_AFTER_IDAT)
        png_ptr->mode |= PNG_HAVE_CHUNK_AFTER_IDAT;

   if (!png_memcmp(png_ptr->chunk_name, png_IHDR, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_IHDR(png_ptr, info_ptr, png_ptr->push_length);
   }
   else if (!png_memcmp(png_ptr->chunk_name, png_IEND, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_IEND(png_ptr, info_ptr, png_ptr->push_length);

      png_ptr->process_mode = PNG_READ_DONE_MODE;
      png_push_have_end(png_ptr, info_ptr);
   }
#ifdef PNG_HANDLE_AS_UNKNOWN_SUPPORTED
   else if (png_handle_as_unknown(png_ptr, png_ptr->chunk_name))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      if (!png_memcmp(png_ptr->chunk_name, png_IDAT, 4))
         png_ptr->mode |= PNG_HAVE_IDAT;
      png_handle_unknown(png_ptr, info_ptr, png_ptr->push_length);
      if (!png_memcmp(png_ptr->chunk_name, png_PLTE, 4))
         png_ptr->mode |= PNG_HAVE_PLTE;
      else if (!png_memcmp(png_ptr->chunk_name, png_IDAT, 4))
      {
         if (!(png_ptr->mode & PNG_HAVE_IHDR))
            png_error(png_ptr, "Missing IHDR before IDAT");
         else if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE &&
                  !(png_ptr->mode & PNG_HAVE_PLTE))
            png_error(png_ptr, "Missing PLTE before IDAT");
      }
   }
#endif
   else if (!png_memcmp(png_ptr->chunk_name, png_PLTE, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_PLTE(png_ptr, info_ptr, png_ptr->push_length);
   }
   else if (!png_memcmp(png_ptr->chunk_name, png_IDAT, 4))
   {
      /* If we reach an IDAT chunk, this means we have read all of the
       * header chunks, and we can start reading the image (or if this
       * is called after the image has been read - we have an error).
       */
     if (!(png_ptr->mode & PNG_HAVE_IHDR))
       png_error(png_ptr, "Missing IHDR before IDAT");
     else if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE &&
         !(png_ptr->mode & PNG_HAVE_PLTE))
       png_error(png_ptr, "Missing PLTE before IDAT");

      if (png_ptr->mode & PNG_HAVE_IDAT)
      {
         if (!(png_ptr->mode & PNG_HAVE_CHUNK_AFTER_IDAT))
           if (png_ptr->push_length == 0)
              return;

         if (png_ptr->mode & PNG_AFTER_IDAT)
            png_error(png_ptr, "Too many IDAT's found");
      }

      png_ptr->idat_size = png_ptr->push_length;
      png_ptr->mode |= PNG_HAVE_IDAT;
      png_ptr->process_mode = PNG_READ_IDAT_MODE;
      png_push_have_info(png_ptr, info_ptr);
      png_ptr->zstream.avail_out = (uInt)png_ptr->irowbytes;
      png_ptr->zstream.next_out = png_ptr->row_buf;
      return;
   }
#if defined(PNG_READ_gAMA_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_gAMA, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_gAMA(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_sBIT_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_sBIT, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_sBIT(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_cHRM_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_cHRM, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_cHRM(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_sRGB_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_sRGB, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_sRGB(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_iCCP_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_iCCP, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_iCCP(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_sPLT_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_sPLT, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_sPLT(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_tRNS_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_tRNS, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_tRNS(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_bKGD_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_bKGD, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_bKGD(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_hIST_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_hIST, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_hIST(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_pHYs_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_pHYs, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_pHYs(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_oFFs_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_oFFs, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_oFFs(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_pCAL_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_pCAL, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_pCAL(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_sCAL_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_sCAL, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_sCAL(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_tIME_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_tIME, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_handle_tIME(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_tEXt_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_tEXt, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_push_handle_tEXt(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_zTXt_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_zTXt, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_push_handle_zTXt(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
#if defined(PNG_READ_iTXt_SUPPORTED)
   else if (!png_memcmp(png_ptr->chunk_name, png_iTXt, 4))
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_push_handle_iTXt(png_ptr, info_ptr, png_ptr->push_length);
   }
#endif
   else
   {
      if (png_ptr->push_length + 4 > png_ptr->buffer_size)
      {
         png_push_save_buffer(png_ptr);
         return;
      }
      png_push_handle_unknown(png_ptr, info_ptr, png_ptr->push_length);
   }

   png_ptr->mode &= ~PNG_HAVE_CHUNK_HEADER;
}