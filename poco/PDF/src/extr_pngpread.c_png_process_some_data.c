#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_10__ {int process_mode; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
#define  PNG_READ_CHUNK_MODE 134 
#define  PNG_READ_IDAT_MODE 133 
#define  PNG_READ_SIG_MODE 132 
#define  PNG_READ_iTXt_MODE 131 
#define  PNG_READ_tEXt_MODE 130 
#define  PNG_READ_zTXt_MODE 129 
#define  PNG_SKIP_MODE 128 
 int /*<<< orphan*/  png_push_crc_finish (TYPE_1__*) ; 
 int /*<<< orphan*/  png_push_read_IDAT (TYPE_1__*) ; 
 int /*<<< orphan*/  png_push_read_chunk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_push_read_iTXt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_push_read_sig (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_push_read_tEXt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_push_read_zTXt (TYPE_1__*,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_process_some_data(png_structp png_ptr, png_infop info_ptr)
{
   if(png_ptr == NULL) return;
   switch (png_ptr->process_mode)
   {
      case PNG_READ_SIG_MODE:
      {
         png_push_read_sig(png_ptr, info_ptr);
         break;
      }
      case PNG_READ_CHUNK_MODE:
      {
         png_push_read_chunk(png_ptr, info_ptr);
         break;
      }
      case PNG_READ_IDAT_MODE:
      {
         png_push_read_IDAT(png_ptr);
         break;
      }
#if defined(PNG_READ_tEXt_SUPPORTED)
      case PNG_READ_tEXt_MODE:
      {
         png_push_read_tEXt(png_ptr, info_ptr);
         break;
      }
#endif
#if defined(PNG_READ_zTXt_SUPPORTED)
      case PNG_READ_zTXt_MODE:
      {
         png_push_read_zTXt(png_ptr, info_ptr);
         break;
      }
#endif
#if defined(PNG_READ_iTXt_SUPPORTED)
      case PNG_READ_iTXt_MODE:
      {
         png_push_read_iTXt(png_ptr, info_ptr);
         break;
      }
#endif
      case PNG_SKIP_MODE:
      {
         png_push_crc_finish(png_ptr);
         break;
      }
      default:
      {
         png_ptr->buffer_size = 0;
         break;
      }
   }
}