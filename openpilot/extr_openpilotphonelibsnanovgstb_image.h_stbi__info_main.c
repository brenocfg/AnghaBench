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
 scalar_t__ stbi__bmp_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int stbi__err (char*,char*) ; 
 scalar_t__ stbi__gif_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi__hdr_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi__jpeg_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi__pic_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi__png_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi__pnm_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi__psd_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi__tga_info (int /*<<< orphan*/ *,int*,int*,int*) ; 

__attribute__((used)) static int stbi__info_main(stbi__context *s, int *x, int *y, int *comp)
{
   #ifndef STBI_NO_JPEG
   if (stbi__jpeg_info(s, x, y, comp)) return 1;
   #endif

   #ifndef STBI_NO_PNG
   if (stbi__png_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_GIF
   if (stbi__gif_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_BMP
   if (stbi__bmp_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_PSD
   if (stbi__psd_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_PIC
   if (stbi__pic_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_PNM
   if (stbi__pnm_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_HDR
   if (stbi__hdr_info(s, x, y, comp))  return 1;
   #endif

   // test tga last because it's a crappy test!
   #ifndef STBI_NO_TGA
   if (stbi__tga_info(s, x, y, comp))
       return 1;
   #endif
   return stbi__err("unknown image type", "Image not of any known type, or corrupt");
}