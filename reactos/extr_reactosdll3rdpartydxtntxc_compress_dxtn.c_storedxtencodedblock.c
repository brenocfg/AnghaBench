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
typedef  int GLushort ;
typedef  int GLuint ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 int ALPHACUT ; 
 int BLUEWEIGHT ; 
 int GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ; 
 int GL_COMPRESSED_RGB_S3TC_DXT1_EXT ; 
 int GREENWEIGHT ; 
 int REDWEIGHT ; 

__attribute__((used)) static void storedxtencodedblock( GLubyte *blkaddr, GLubyte srccolors[4][4][4], GLubyte *bestcolor[2],
                           GLint numxpixels, GLint numypixels, GLuint type, GLboolean haveAlpha)
{
   /* use same luminance-weighted distance metric to determine encoding as for finding the base colors */

   GLint i, j, colors;
   GLuint testerror, testerror2, pixerror, pixerrorbest;
   GLint colordist;
   GLushort color0, color1, tempcolor;
   GLuint bits = 0, bits2 = 0;
   GLubyte *colorptr;
   GLubyte enc = 0;
   GLubyte cv[4][4];

   bestcolor[0][0] = bestcolor[0][0] & 0xf8;
   bestcolor[0][1] = bestcolor[0][1] & 0xfc;
   bestcolor[0][2] = bestcolor[0][2] & 0xf8;
   bestcolor[1][0] = bestcolor[1][0] & 0xf8;
   bestcolor[1][1] = bestcolor[1][1] & 0xfc;
   bestcolor[1][2] = bestcolor[1][2] & 0xf8;

   color0 = bestcolor[0][0] << 8 | bestcolor[0][1] << 3 | bestcolor[0][2] >> 3;
   color1 = bestcolor[1][0] << 8 | bestcolor[1][1] << 3 | bestcolor[1][2] >> 3;
   if (color0 < color1) {
      tempcolor = color0; color0 = color1; color1 = tempcolor;
      colorptr = bestcolor[0]; bestcolor[0] = bestcolor[1]; bestcolor[1] = colorptr;
   }


   for (i = 0; i < 3; i++) {
      cv[0][i] = bestcolor[0][i];
      cv[1][i] = bestcolor[1][i];
      cv[2][i] = (bestcolor[0][i] * 2 + bestcolor[1][i]) / 3;
      cv[3][i] = (bestcolor[0][i] + bestcolor[1][i] * 2) / 3;
   }

   testerror = 0;
   for (j = 0; j < numypixels; j++) {
      for (i = 0; i < numxpixels; i++) {
         pixerrorbest = 0xffffffff;
         for (colors = 0; colors < 4; colors++) {
            colordist = srccolors[j][i][0] - cv[colors][0];
            pixerror = colordist * colordist * REDWEIGHT;
            colordist = srccolors[j][i][1] - cv[colors][1];
            pixerror += colordist * colordist * GREENWEIGHT;
            colordist = srccolors[j][i][2] - cv[colors][2];
            pixerror += colordist * colordist * BLUEWEIGHT;
            if (pixerror < pixerrorbest) {
               pixerrorbest = pixerror;
               enc = colors;
            }
         }
         testerror += pixerrorbest;
         bits |= enc << (2 * (j * 4 + i));
      }
   }
   /* some hw might disagree but actually decoding should always use 4-color encoding
      for non-dxt1 formats */
   if (type == GL_COMPRESSED_RGB_S3TC_DXT1_EXT || type == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) {
      for (i = 0; i < 3; i++) {
         cv[2][i] = (bestcolor[0][i] + bestcolor[1][i]) / 2;
         /* this isn't used. Looks like the black color constant can only be used
            with RGB_DXT1 if I read the spec correctly (note though that the radeon gpu disagrees,
            it will decode 3 to black even with DXT3/5), and due to how the color searching works
            it won't get used even then */
         cv[3][i] = 0;
      }
      testerror2 = 0;
      for (j = 0; j < numypixels; j++) {
         for (i = 0; i < numxpixels; i++) {
            pixerrorbest = 0xffffffff;
            if ((type == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) && (srccolors[j][i][3] <= ALPHACUT)) {
               enc = 3;
               pixerrorbest = 0; /* don't calculate error */
            }
            else {
               /* we're calculating the same what we have done already for colors 0-1 above... */
               for (colors = 0; colors < 3; colors++) {
                  colordist = srccolors[j][i][0] - cv[colors][0];
                  pixerror = colordist * colordist * REDWEIGHT;
                  colordist = srccolors[j][i][1] - cv[colors][1];
                  pixerror += colordist * colordist * GREENWEIGHT;
                  colordist = srccolors[j][i][2] - cv[colors][2];
                  pixerror += colordist * colordist * BLUEWEIGHT;
                  if (pixerror < pixerrorbest) {
                     pixerrorbest = pixerror;
                     /* need to exchange colors later */
                     if (colors > 1) enc = colors;
                     else enc = colors ^ 1;
                  }
               }
            }
            testerror2 += pixerrorbest;
            bits2 |= enc << (2 * (j * 4 + i));
         }
      }
   } else {
      testerror2 = 0xffffffff;
   }

   /* finally we're finished, write back colors and bits */
   if ((testerror > testerror2) || (haveAlpha)) {
      *blkaddr++ = color1 & 0xff;
      *blkaddr++ = color1 >> 8;
      *blkaddr++ = color0 & 0xff;
      *blkaddr++ = color0 >> 8;
      *blkaddr++ = bits2 & 0xff;
      *blkaddr++ = ( bits2 >> 8) & 0xff;
      *blkaddr++ = ( bits2 >> 16) & 0xff;
      *blkaddr = bits2 >> 24;
   }
   else {
      *blkaddr++ = color0 & 0xff;
      *blkaddr++ = color0 >> 8;
      *blkaddr++ = color1 & 0xff;
      *blkaddr++ = color1 >> 8;
      *blkaddr++ = bits & 0xff;
      *blkaddr++ = ( bits >> 8) & 0xff;
      *blkaddr++ = ( bits >> 16) & 0xff;
      *blkaddr = bits >> 24;
   }
}