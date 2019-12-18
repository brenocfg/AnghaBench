#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structp ;
typedef  size_t png_size_t ;
typedef  TYPE_2__* png_infop ;
typedef  int* png_charp ;
typedef  int* png_bytep ;
typedef  int png_byte ;
struct TYPE_15__ {int valid; } ;
struct TYPE_14__ {int mode; } ;

/* Variables and functions */
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int PNG_INFO_iCCP ; 
 scalar_t__ png_crc_finish (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int*,size_t) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int* png_decompress_chunk (TYPE_1__*,int,int*,size_t,size_t,size_t*) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_free (TYPE_1__*,int*) ; 
 scalar_t__ png_malloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  png_set_iCCP (TYPE_1__*,TYPE_2__*,int*,int,int*,scalar_t__) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 

void /* PRIVATE */
png_handle_iCCP(png_structp png_ptr, png_infop info_ptr, png_uint_32 length)
/* Note: this does not properly handle chunks that are > 64K under DOS */
{
   png_charp chunkdata;
   png_byte compression_type;
   png_bytep pC;
   png_charp profile;
   png_uint_32 skip = 0;
   png_uint_32 profile_size, profile_length;
   png_size_t slength, prefix_length, data_length;

   png_debug(1, "in png_handle_iCCP\n");

   if (!(png_ptr->mode & PNG_HAVE_IHDR))
      png_error(png_ptr, "Missing IHDR before iCCP");
   else if (png_ptr->mode & PNG_HAVE_IDAT)
   {
      png_warning(png_ptr, "Invalid iCCP after IDAT");
      png_crc_finish(png_ptr, length);
      return;
   }
   else if (png_ptr->mode & PNG_HAVE_PLTE)
      /* Should be an error, but we can cope with it */
      png_warning(png_ptr, "Out of place iCCP chunk");

   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_iCCP))
   {
      png_warning(png_ptr, "Duplicate iCCP chunk");
      png_crc_finish(png_ptr, length);
      return;
   }

#ifdef PNG_MAX_MALLOC_64K
   if (length > (png_uint_32)65535L)
   {
      png_warning(png_ptr, "iCCP chunk too large to fit in memory");
      skip = length - (png_uint_32)65535L;
      length = (png_uint_32)65535L;
   }
#endif

   chunkdata = (png_charp)png_malloc(png_ptr, length + 1);
   slength = (png_size_t)length;
   png_crc_read(png_ptr, (png_bytep)chunkdata, slength);

   if (png_crc_finish(png_ptr, skip))
   {
      png_free(png_ptr, chunkdata);
      return;
   }

   chunkdata[slength] = 0x00;

   for (profile = chunkdata; *profile; profile++)
      /* empty loop to find end of name */ ;

   ++profile;

   /* there should be at least one zero (the compression type byte)
      following the separator, and we should be on it  */
   if ( profile >= chunkdata + slength - 1)
   {
      png_free(png_ptr, chunkdata);
      png_warning(png_ptr, "Malformed iCCP chunk");
      return;
   }

   /* compression_type should always be zero */
   compression_type = *profile++;
   if (compression_type)
   {
      png_warning(png_ptr, "Ignoring nonzero compression type in iCCP chunk");
      compression_type=0x00;  /* Reset it to zero (libpng-1.0.6 through 1.0.8
                                 wrote nonzero) */
   }

   prefix_length = profile - chunkdata;
   chunkdata = png_decompress_chunk(png_ptr, compression_type, chunkdata,
                                    slength, prefix_length, &data_length);

   profile_length = data_length - prefix_length;

   if ( prefix_length > data_length || profile_length < 4)
   {
      png_free(png_ptr, chunkdata);
      png_warning(png_ptr, "Profile size field missing from iCCP chunk");
      return;
   }

   /* Check the profile_size recorded in the first 32 bits of the ICC profile */
   pC = (png_bytep)(chunkdata+prefix_length);
   profile_size = ((*(pC  ))<<24) |
                  ((*(pC+1))<<16) |
                  ((*(pC+2))<< 8) |
                  ((*(pC+3))    );

   if(profile_size < profile_length)
      profile_length = profile_size;

   if(profile_size > profile_length)
   {
      png_free(png_ptr, chunkdata);
      png_warning(png_ptr, "Ignoring truncated iCCP profile.");
      return;
   }

   png_set_iCCP(png_ptr, info_ptr, chunkdata, compression_type,
                chunkdata + prefix_length, profile_length);
   png_free(png_ptr, chunkdata);
}