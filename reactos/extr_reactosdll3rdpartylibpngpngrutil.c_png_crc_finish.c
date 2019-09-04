#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  chunk_name; } ;

/* Variables and functions */
 scalar_t__ PNG_CHUNK_ANCILLARY (int /*<<< orphan*/ ) ; 
 int PNG_FLAG_CRC_ANCILLARY_NOWARN ; 
 int PNG_FLAG_CRC_CRITICAL_USE ; 
 int PNG_INFLATE_BUF_SIZE ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_chunk_warning (TYPE_1__*,char*) ; 
 scalar_t__ png_crc_error (TYPE_1__*) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

int /* PRIVATE */
png_crc_finish(png_structrp png_ptr, png_uint_32 skip)
{
   /* The size of the local buffer for inflate is a good guess as to a
    * reasonable size to use for buffering reads from the application.
    */
   while (skip > 0)
   {
      png_uint_32 len;
      png_byte tmpbuf[PNG_INFLATE_BUF_SIZE];

      len = (sizeof tmpbuf);
      if (len > skip)
         len = skip;
      skip -= len;

      png_crc_read(png_ptr, tmpbuf, len);
   }

   if (png_crc_error(png_ptr) != 0)
   {
      if (PNG_CHUNK_ANCILLARY(png_ptr->chunk_name) != 0 ?
          (png_ptr->flags & PNG_FLAG_CRC_ANCILLARY_NOWARN) == 0 :
          (png_ptr->flags & PNG_FLAG_CRC_CRITICAL_USE) != 0)
      {
         png_chunk_warning(png_ptr, "CRC error");
      }

      else
         png_chunk_error(png_ptr, "CRC error");

      return (1);
   }

   return (0);
}