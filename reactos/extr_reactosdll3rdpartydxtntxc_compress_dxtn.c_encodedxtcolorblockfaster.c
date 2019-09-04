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
typedef  size_t GLuint ;
typedef  size_t GLubyte ;
typedef  size_t GLint ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 size_t ALPHACUT ; 
 size_t BLUEWEIGHT ; 
 size_t GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 size_t GREENWEIGHT ; 
 size_t REDWEIGHT ; 
 int /*<<< orphan*/  fancybasecolorsearch (size_t*,size_t***,size_t**,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storedxtencodedblock (size_t*,size_t***,size_t**,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encodedxtcolorblockfaster( GLubyte *blkaddr, GLubyte srccolors[4][4][4],
                         GLint numxpixels, GLint numypixels, GLuint type )
{
/* simplistic approach. We need two base colors, simply use the "highest" and the "lowest" color
   present in the picture as base colors */

   /* define lowest and highest color as shortest and longest vector to 0/0/0, though the
      vectors are weighted similar to their importance in rgb-luminance conversion
      doesn't work too well though...
      This seems to be a rather difficult problem */

   GLubyte *bestcolor[2];
   GLubyte basecolors[2][3];
   GLubyte i, j;
   GLuint lowcv, highcv, testcv;
   GLboolean haveAlpha = GL_FALSE;

   lowcv = highcv = srccolors[0][0][0] * srccolors[0][0][0] * REDWEIGHT +
                          srccolors[0][0][1] * srccolors[0][0][1] * GREENWEIGHT +
                          srccolors[0][0][2] * srccolors[0][0][2] * BLUEWEIGHT;
   bestcolor[0] = bestcolor[1] = srccolors[0][0];
   for (j = 0; j < numypixels; j++) {
      for (i = 0; i < numxpixels; i++) {
         /* don't use this as a base color if the pixel will get black/transparent anyway */
         if ((type != GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) || (srccolors[j][i][3] > ALPHACUT)) {
            testcv = srccolors[j][i][0] * srccolors[j][i][0] * REDWEIGHT +
                     srccolors[j][i][1] * srccolors[j][i][1] * GREENWEIGHT +
                     srccolors[j][i][2] * srccolors[j][i][2] * BLUEWEIGHT;
            if (testcv > highcv) {
               highcv = testcv;
               bestcolor[1] = srccolors[j][i];
            }
            else if (testcv < lowcv) {
               lowcv = testcv;
               bestcolor[0] = srccolors[j][i];
            }
         }
         else haveAlpha = GL_TRUE;
      }
   }
   /* make sure the original color values won't get touched... */
   for (j = 0; j < 2; j++) {
      for (i = 0; i < 3; i++) {
         basecolors[j][i] = bestcolor[j][i];
      }
   }
   bestcolor[0] = basecolors[0];
   bestcolor[1] = basecolors[1];

   /* try to find better base colors */
   fancybasecolorsearch(blkaddr, srccolors, bestcolor, numxpixels, numypixels, type, haveAlpha);
   /* find the best encoding for these colors, and store the result */
   storedxtencodedblock(blkaddr, srccolors, bestcolor, numxpixels, numypixels, type, haveAlpha);
}