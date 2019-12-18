#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* resample_row_hv_2_kernel; void* YCbCr_to_RGB_kernel; void* idct_block_kernel; } ;
typedef  TYPE_1__ stbi__jpeg ;

/* Variables and functions */
 void* stbi__YCbCr_to_RGB_row ; 
 void* stbi__YCbCr_to_RGB_simd ; 
 void* stbi__idct_block ; 
 void* stbi__idct_simd ; 
 void* stbi__resample_row_hv_2 ; 
 void* stbi__resample_row_hv_2_simd ; 
 scalar_t__ stbi__sse2_available () ; 

__attribute__((used)) static void stbi__setup_jpeg(stbi__jpeg *j)
{
   j->idct_block_kernel = stbi__idct_block;
   j->YCbCr_to_RGB_kernel = stbi__YCbCr_to_RGB_row;
   j->resample_row_hv_2_kernel = stbi__resample_row_hv_2;

#ifdef STBI_SSE2
   if (stbi__sse2_available()) {
      j->idct_block_kernel = stbi__idct_simd;
      #ifndef STBI_JPEG_OLD
      j->YCbCr_to_RGB_kernel = stbi__YCbCr_to_RGB_simd;
      #endif
      j->resample_row_hv_2_kernel = stbi__resample_row_hv_2_simd;
   }
#endif

#ifdef STBI_NEON
   j->idct_block_kernel = stbi__idct_simd;
   #ifndef STBI_JPEG_OLD
   j->YCbCr_to_RGB_kernel = stbi__YCbCr_to_RGB_simd;
   #endif
   j->resample_row_hv_2_kernel = stbi__resample_row_hv_2_simd;
#endif
}