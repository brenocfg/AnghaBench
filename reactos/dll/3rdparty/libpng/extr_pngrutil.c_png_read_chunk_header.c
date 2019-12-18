#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_9__ {void* io_state; scalar_t__ chunk_name; } ;

/* Variables and functions */
 scalar_t__ PNG_CHUNK_FROM_STRING (int /*<<< orphan*/ *) ; 
 void* PNG_IO_CHUNK_DATA ; 
 void* PNG_IO_CHUNK_HDR ; 
 void* PNG_IO_READING ; 
 int /*<<< orphan*/  png_calculate_crc (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_check_chunk_length (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  png_check_chunk_name (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  png_debug2 (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 scalar_t__ png_get_uint_31 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_data (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_reset_crc (TYPE_1__*) ; 

png_uint_32 /* PRIVATE */
png_read_chunk_header(png_structrp png_ptr)
{
   png_byte buf[8];
   png_uint_32 length;

#ifdef PNG_IO_STATE_SUPPORTED
   png_ptr->io_state = PNG_IO_READING | PNG_IO_CHUNK_HDR;
#endif

   /* Read the length and the chunk name.
    * This must be performed in a single I/O call.
    */
   png_read_data(png_ptr, buf, 8);
   length = png_get_uint_31(png_ptr, buf);

   /* Put the chunk name into png_ptr->chunk_name. */
   png_ptr->chunk_name = PNG_CHUNK_FROM_STRING(buf+4);

   png_debug2(0, "Reading %lx chunk, length = %lu",
       (unsigned long)png_ptr->chunk_name, (unsigned long)length);

   /* Reset the crc and run it over the chunk name. */
   png_reset_crc(png_ptr);
   png_calculate_crc(png_ptr, buf + 4, 4);

   /* Check to see if chunk name is valid. */
   png_check_chunk_name(png_ptr, png_ptr->chunk_name);

   /* Check for too-large chunk length */
   png_check_chunk_length(png_ptr, length);

#ifdef PNG_IO_STATE_SUPPORTED
   png_ptr->io_state = PNG_IO_READING | PNG_IO_CHUNK_DATA;
#endif

   return length;
}