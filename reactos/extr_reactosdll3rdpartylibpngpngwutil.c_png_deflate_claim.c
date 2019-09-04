#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int png_alloc_size_t ;
struct TYPE_10__ {scalar_t__ avail_out; int /*<<< orphan*/ * next_out; scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_9__ {scalar_t__ zowner; int zlib_level; int zlib_method; int zlib_window_bits; int zlib_mem_level; int flags; int zlib_strategy; scalar_t__ do_filter; int zlib_set_level; int zlib_set_method; int zlib_set_window_bits; int zlib_set_mem_level; int zlib_set_strategy; TYPE_6__ zstream; } ;

/* Variables and functions */
 scalar_t__ PNG_FILTER_NONE ; 
 int PNG_FLAG_ZLIB_CUSTOM_STRATEGY ; 
 int PNG_FLAG_ZSTREAM_INITIALIZED ; 
 int PNG_Z_DEFAULT_NOFILTER_STRATEGY ; 
 int PNG_Z_DEFAULT_STRATEGY ; 
 int Z_DEFAULT_STRATEGY ; 
 int Z_OK ; 
 int deflateEnd (TYPE_6__*) ; 
 int deflateInit2 (TYPE_6__*,int,int,int,int,int) ; 
 int deflateReset (TYPE_6__*) ; 
 int /*<<< orphan*/  msg ; 
 scalar_t__ png_IDAT ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_zstream_error (TYPE_1__*,int) ; 

__attribute__((used)) static int
png_deflate_claim(png_structrp png_ptr, png_uint_32 owner,
    png_alloc_size_t data_size)
{
   if (png_ptr->zowner != 0)
   {
#if defined(PNG_WARNINGS_SUPPORTED) || defined(PNG_ERROR_TEXT_SUPPORTED)
      char msg[64];

      PNG_STRING_FROM_CHUNK(msg, owner);
      msg[4] = ':';
      msg[5] = ' ';
      PNG_STRING_FROM_CHUNK(msg+6, png_ptr->zowner);
      /* So the message that results is "<chunk> using zstream"; this is an
       * internal error, but is very useful for debugging.  i18n requirements
       * are minimal.
       */
      (void)png_safecat(msg, (sizeof msg), 10, " using zstream");
#endif
#if PNG_RELEASE_BUILD
         png_warning(png_ptr, msg);

         /* Attempt sane error recovery */
         if (png_ptr->zowner == png_IDAT) /* don't steal from IDAT */
         {
            png_ptr->zstream.msg = PNGZ_MSG_CAST("in use by IDAT");
            return Z_STREAM_ERROR;
         }

         png_ptr->zowner = 0;
#else
         png_error(png_ptr, msg);
#endif
   }

   {
      int level = png_ptr->zlib_level;
      int method = png_ptr->zlib_method;
      int windowBits = png_ptr->zlib_window_bits;
      int memLevel = png_ptr->zlib_mem_level;
      int strategy; /* set below */
      int ret; /* zlib return code */

      if (owner == png_IDAT)
      {
         if ((png_ptr->flags & PNG_FLAG_ZLIB_CUSTOM_STRATEGY) != 0)
            strategy = png_ptr->zlib_strategy;

         else if (png_ptr->do_filter != PNG_FILTER_NONE)
            strategy = PNG_Z_DEFAULT_STRATEGY;

         else
            strategy = PNG_Z_DEFAULT_NOFILTER_STRATEGY;
      }

      else
      {
#ifdef PNG_WRITE_CUSTOMIZE_ZTXT_COMPRESSION_SUPPORTED
            level = png_ptr->zlib_text_level;
            method = png_ptr->zlib_text_method;
            windowBits = png_ptr->zlib_text_window_bits;
            memLevel = png_ptr->zlib_text_mem_level;
            strategy = png_ptr->zlib_text_strategy;
#else
            /* If customization is not supported the values all come from the
             * IDAT values except for the strategy, which is fixed to the
             * default.  (This is the pre-1.6.0 behavior too, although it was
             * implemented in a very different way.)
             */
            strategy = Z_DEFAULT_STRATEGY;
#endif
      }

      /* Adjust 'windowBits' down if larger than 'data_size'; to stop this
       * happening just pass 32768 as the data_size parameter.  Notice that zlib
       * requires an extra 262 bytes in the window in addition to the data to be
       * able to see the whole of the data, so if data_size+262 takes us to the
       * next windowBits size we need to fix up the value later.  (Because even
       * though deflate needs the extra window, inflate does not!)
       */
      if (data_size <= 16384)
      {
         /* IMPLEMENTATION NOTE: this 'half_window_size' stuff is only here to
          * work round a Microsoft Visual C misbehavior which, contrary to C-90,
          * widens the result of the following shift to 64-bits if (and,
          * apparently, only if) it is used in a test.
          */
         unsigned int half_window_size = 1U << (windowBits-1);

         while (data_size + 262 <= half_window_size)
         {
            half_window_size >>= 1;
            --windowBits;
         }
      }

      /* Check against the previous initialized values, if any. */
      if ((png_ptr->flags & PNG_FLAG_ZSTREAM_INITIALIZED) != 0 &&
         (png_ptr->zlib_set_level != level ||
         png_ptr->zlib_set_method != method ||
         png_ptr->zlib_set_window_bits != windowBits ||
         png_ptr->zlib_set_mem_level != memLevel ||
         png_ptr->zlib_set_strategy != strategy))
      {
         if (deflateEnd(&png_ptr->zstream) != Z_OK)
            png_warning(png_ptr, "deflateEnd failed (ignored)");

         png_ptr->flags &= ~PNG_FLAG_ZSTREAM_INITIALIZED;
      }

      /* For safety clear out the input and output pointers (currently zlib
       * doesn't use them on Init, but it might in the future).
       */
      png_ptr->zstream.next_in = NULL;
      png_ptr->zstream.avail_in = 0;
      png_ptr->zstream.next_out = NULL;
      png_ptr->zstream.avail_out = 0;

      /* Now initialize if required, setting the new parameters, otherwise just
       * do a simple reset to the previous parameters.
       */
      if ((png_ptr->flags & PNG_FLAG_ZSTREAM_INITIALIZED) != 0)
         ret = deflateReset(&png_ptr->zstream);

      else
      {
         ret = deflateInit2(&png_ptr->zstream, level, method, windowBits,
             memLevel, strategy);

         if (ret == Z_OK)
            png_ptr->flags |= PNG_FLAG_ZSTREAM_INITIALIZED;
      }

      /* The return code is from either deflateReset or deflateInit2; they have
       * pretty much the same set of error codes.
       */
      if (ret == Z_OK)
         png_ptr->zowner = owner;

      else
         png_zstream_error(png_ptr, ret);

      return ret;
   }
}