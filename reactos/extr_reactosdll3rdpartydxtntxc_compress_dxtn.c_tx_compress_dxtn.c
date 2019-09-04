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
typedef  int GLubyte ;
typedef  int GLint ;
typedef  int GLenum ;
typedef  int GLchan ;

/* Variables and functions */
#define  GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 131 
#define  GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 130 
#define  GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 129 
#define  GL_COMPRESSED_RGB_S3TC_DXT1_EXT 128 
 int /*<<< orphan*/  encodedxt5alpha (int*,int***,int,int) ; 
 int /*<<< orphan*/  encodedxtcolorblockfaster (int*,int***,int,int,int) ; 
 int /*<<< orphan*/  extractsrccolors (int***,int const*,int,int,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

void tx_compress_dxtn(GLint srccomps, GLint width, GLint height, const GLubyte *srcPixData,
                     GLenum destFormat, GLubyte *dest, GLint dstRowStride)
{
      GLubyte *blkaddr = dest;
      GLubyte srcpixels[4][4][4];
      const GLchan *srcaddr = srcPixData;
      GLint numxpixels, numypixels;
      GLint i, j;
      GLint dstRowDiff;

   switch (destFormat) {
   case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
   case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
      /* hmm we used to get called without dstRowStride... */
      dstRowDiff = dstRowStride >= (width * 2) ? dstRowStride - (((width + 3) & ~3) * 2) : 0;
/*      fprintf(stderr, "dxt1 tex width %d tex height %d dstRowStride %d\n",
              width, height, dstRowStride); */
      for (j = 0; j < height; j += 4) {
         if (height > j + 3) numypixels = 4;
         else numypixels = height - j;
         srcaddr = srcPixData + j * width * srccomps;
         for (i = 0; i < width; i += 4) {
            if (width > i + 3) numxpixels = 4;
            else numxpixels = width - i;
            extractsrccolors(srcpixels, srcaddr, width, numxpixels, numypixels, srccomps);
            encodedxtcolorblockfaster(blkaddr, srcpixels, numxpixels, numypixels, destFormat);
            srcaddr += srccomps * numxpixels;
            blkaddr += 8;
         }
         blkaddr += dstRowDiff;
      }
      break;
   case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
      dstRowDiff = dstRowStride >= (width * 4) ? dstRowStride - (((width + 3) & ~3) * 4) : 0;
/*      fprintf(stderr, "dxt3 tex width %d tex height %d dstRowStride %d\n",
              width, height, dstRowStride); */
      for (j = 0; j < height; j += 4) {
         if (height > j + 3) numypixels = 4;
         else numypixels = height - j;
         srcaddr = srcPixData + j * width * srccomps;
         for (i = 0; i < width; i += 4) {
            if (width > i + 3) numxpixels = 4;
            else numxpixels = width - i;
            extractsrccolors(srcpixels, srcaddr, width, numxpixels, numypixels, srccomps);
            *blkaddr++ = (srcpixels[0][0][3] >> 4) | (srcpixels[0][1][3] & 0xf0);
            *blkaddr++ = (srcpixels[0][2][3] >> 4) | (srcpixels[0][3][3] & 0xf0);
            *blkaddr++ = (srcpixels[1][0][3] >> 4) | (srcpixels[1][1][3] & 0xf0);
            *blkaddr++ = (srcpixels[1][2][3] >> 4) | (srcpixels[1][3][3] & 0xf0);
            *blkaddr++ = (srcpixels[2][0][3] >> 4) | (srcpixels[2][1][3] & 0xf0);
            *blkaddr++ = (srcpixels[2][2][3] >> 4) | (srcpixels[2][3][3] & 0xf0);
            *blkaddr++ = (srcpixels[3][0][3] >> 4) | (srcpixels[3][1][3] & 0xf0);
            *blkaddr++ = (srcpixels[3][2][3] >> 4) | (srcpixels[3][3][3] & 0xf0);
            encodedxtcolorblockfaster(blkaddr, srcpixels, numxpixels, numypixels, destFormat);
            srcaddr += srccomps * numxpixels;
            blkaddr += 8;
         }
         blkaddr += dstRowDiff;
      }
      break;
   case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
      dstRowDiff = dstRowStride >= (width * 4) ? dstRowStride - (((width + 3) & ~3) * 4) : 0;
/*      fprintf(stderr, "dxt5 tex width %d tex height %d dstRowStride %d\n",
              width, height, dstRowStride); */
      for (j = 0; j < height; j += 4) {
         if (height > j + 3) numypixels = 4;
         else numypixels = height - j;
         srcaddr = srcPixData + j * width * srccomps;
         for (i = 0; i < width; i += 4) {
            if (width > i + 3) numxpixels = 4;
            else numxpixels = width - i;
            extractsrccolors(srcpixels, srcaddr, width, numxpixels, numypixels, srccomps);
            encodedxt5alpha(blkaddr, srcpixels, numxpixels, numypixels);
            encodedxtcolorblockfaster(blkaddr + 8, srcpixels, numxpixels, numypixels, destFormat);
            srcaddr += srccomps * numxpixels;
            blkaddr += 16;
         }
         blkaddr += dstRowDiff;
      }
      break;
   default:
      fprintf(stderr, "libdxtn: Bad dstFormat %d in tx_compress_dxtn\n", destFormat);
      return;
   }
}