#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 unsigned char* stbi__bmp_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__bmp_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi__errpuc (char*,char*) ; 
 unsigned char* stbi__gif_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__gif_test (int /*<<< orphan*/ *) ; 
 float* stbi__hdr_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__hdr_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi__hdr_to_ldr (float*,int,int,int) ; 
 unsigned char* stbi__jpeg_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__jpeg_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi__pic_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__pic_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi__png_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__png_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi__pnm_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__pnm_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi__psd_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__psd_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi__tga_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__tga_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned char *stbi__load_main(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
   #ifndef STBI_NO_JPEG
   if (stbi__jpeg_test(s)) return stbi__jpeg_load(s,x,y,comp,req_comp);
   #endif
   #ifndef STBI_NO_PNG
   if (stbi__png_test(s))  return stbi__png_load(s,x,y,comp,req_comp);
   #endif
   #ifndef STBI_NO_BMP
   if (stbi__bmp_test(s))  return stbi__bmp_load(s,x,y,comp,req_comp);
   #endif
   #ifndef STBI_NO_GIF
   if (stbi__gif_test(s))  return stbi__gif_load(s,x,y,comp,req_comp);
   #endif
   #ifndef STBI_NO_PSD
   if (stbi__psd_test(s))  return stbi__psd_load(s,x,y,comp,req_comp);
   #endif
   #ifndef STBI_NO_PIC
   if (stbi__pic_test(s))  return stbi__pic_load(s,x,y,comp,req_comp);
   #endif
   #ifndef STBI_NO_PNM
   if (stbi__pnm_test(s))  return stbi__pnm_load(s,x,y,comp,req_comp);
   #endif

   #ifndef STBI_NO_HDR
   if (stbi__hdr_test(s)) {
      float *hdr = stbi__hdr_load(s, x,y,comp,req_comp);
      return stbi__hdr_to_ldr(hdr, *x, *y, req_comp ? req_comp : *comp);
   }
   #endif

   #ifndef STBI_NO_TGA
   // test tga last because it's a crappy test!
   if (stbi__tga_test(s))
      return stbi__tga_load(s,x,y,comp,req_comp);
   #endif

   return stbi__errpuc("unknown image type", "Image not of any known type, or corrupt");
}