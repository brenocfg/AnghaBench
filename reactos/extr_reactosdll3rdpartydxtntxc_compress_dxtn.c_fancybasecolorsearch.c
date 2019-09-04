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
typedef  int GLuint ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int BLUEWEIGHT ; 
 int GREENWEIGHT ; 
 int REDWEIGHT ; 
 int abs (int) ; 

__attribute__((used)) static void fancybasecolorsearch( GLubyte *blkaddr, GLubyte srccolors[4][4][4], GLubyte *bestcolor[2],
                           GLint numxpixels, GLint numypixels, GLint type, GLboolean haveAlpha)
{
   /* use same luminance-weighted distance metric to determine encoding as for finding the base colors */

   /* TODO could also try to find a better encoding for the 3-color-encoding type, this really should be done
      if it's rgba_dxt1 and we have alpha in the block, currently even values which will be mapped to black
      due to their alpha value will influence the result */
   GLint i, j, colors, z;
   GLuint pixerror, pixerrorred, pixerrorgreen, pixerrorblue, pixerrorbest;
   GLint colordist, blockerrlin[2][3];
   GLubyte nrcolor[2];
   GLint pixerrorcolorbest[3];
   GLubyte enc = 0;
   GLubyte cv[4][4];
   GLubyte testcolor[2][3];

/*   fprintf(stderr, "color begin 0 r/g/b %d/%d/%d, 1 r/g/b %d/%d/%d\n",
      bestcolor[0][0], bestcolor[0][1], bestcolor[0][2], bestcolor[1][0], bestcolor[1][1], bestcolor[1][2]);*/
   if (((bestcolor[0][0] & 0xf8) << 8 | (bestcolor[0][1] & 0xfc) << 3 | bestcolor[0][2] >> 3) <
      ((bestcolor[1][0] & 0xf8) << 8 | (bestcolor[1][1] & 0xfc) << 3 | bestcolor[1][2] >> 3)) {
      testcolor[0][0] = bestcolor[0][0];
      testcolor[0][1] = bestcolor[0][1];
      testcolor[0][2] = bestcolor[0][2];
      testcolor[1][0] = bestcolor[1][0];
      testcolor[1][1] = bestcolor[1][1];
      testcolor[1][2] = bestcolor[1][2];
   }
   else {
      testcolor[1][0] = bestcolor[0][0];
      testcolor[1][1] = bestcolor[0][1];
      testcolor[1][2] = bestcolor[0][2];
      testcolor[0][0] = bestcolor[1][0];
      testcolor[0][1] = bestcolor[1][1];
      testcolor[0][2] = bestcolor[1][2];
   }

   for (i = 0; i < 3; i ++) {
      cv[0][i] = testcolor[0][i];
      cv[1][i] = testcolor[1][i];
      cv[2][i] = (testcolor[0][i] * 2 + testcolor[1][i]) / 3;
      cv[3][i] = (testcolor[0][i] + testcolor[1][i] * 2) / 3;
   }

   blockerrlin[0][0] = 0;
   blockerrlin[0][1] = 0;
   blockerrlin[0][2] = 0;
   blockerrlin[1][0] = 0;
   blockerrlin[1][1] = 0;
   blockerrlin[1][2] = 0;

   nrcolor[0] = 0;
   nrcolor[1] = 0;

   for (j = 0; j < numypixels; j++) {
      for (i = 0; i < numxpixels; i++) {
         pixerrorbest = 0xffffffff;
         for (colors = 0; colors < 4; colors++) {
            colordist = srccolors[j][i][0] - (cv[colors][0]);
            pixerror = colordist * colordist * REDWEIGHT;
            pixerrorred = colordist;
            colordist = srccolors[j][i][1] - (cv[colors][1]);
            pixerror += colordist * colordist * GREENWEIGHT;
            pixerrorgreen = colordist;
            colordist = srccolors[j][i][2] - (cv[colors][2]);
            pixerror += colordist * colordist * BLUEWEIGHT;
            pixerrorblue = colordist;
            if (pixerror < pixerrorbest) {
               enc = colors;
               pixerrorbest = pixerror;
               pixerrorcolorbest[0] = pixerrorred;
               pixerrorcolorbest[1] = pixerrorgreen;
               pixerrorcolorbest[2] = pixerrorblue;
            }
         }
         if (enc == 0) {
            for (z = 0; z < 3; z++) {
               blockerrlin[0][z] += 3 * pixerrorcolorbest[z];
            }
            nrcolor[0] += 3;
         }
         else if (enc == 2) {
            for (z = 0; z < 3; z++) {
               blockerrlin[0][z] += 2 * pixerrorcolorbest[z];
            }
            nrcolor[0] += 2;
            for (z = 0; z < 3; z++) {
               blockerrlin[1][z] += 1 * pixerrorcolorbest[z];
            }
            nrcolor[1] += 1;
         }
         else if (enc == 3) {
            for (z = 0; z < 3; z++) {
               blockerrlin[0][z] += 1 * pixerrorcolorbest[z];
            }
            nrcolor[0] += 1;
            for (z = 0; z < 3; z++) {
               blockerrlin[1][z] += 2 * pixerrorcolorbest[z];
            }
            nrcolor[1] += 2;
         }
         else if (enc == 1) {
            for (z = 0; z < 3; z++) {
               blockerrlin[1][z] += 3 * pixerrorcolorbest[z];
            }
            nrcolor[1] += 3;
         }
      }
   }
   if (nrcolor[0] == 0) nrcolor[0] = 1;
   if (nrcolor[1] == 0) nrcolor[1] = 1;
   for (j = 0; j < 2; j++) {
      for (i = 0; i < 3; i++) {
	 GLint newvalue = testcolor[j][i] + blockerrlin[j][i] / nrcolor[j];
	 if (newvalue <= 0)
	    testcolor[j][i] = 0;
	 else if (newvalue >= 255)
	    testcolor[j][i] = 255;
	 else testcolor[j][i] = newvalue;
      }
   }

   if ((abs(testcolor[0][0] - testcolor[1][0]) < 8) &&
       (abs(testcolor[0][1] - testcolor[1][1]) < 4) &&
       (abs(testcolor[0][2] - testcolor[1][2]) < 8)) {
       /* both colors are so close they might get encoded as the same 16bit values */
      GLubyte coldiffred, coldiffgreen, coldiffblue, coldiffmax, factor, ind0, ind1;

      coldiffred = abs(testcolor[0][0] - testcolor[1][0]);
      coldiffgreen = 2 * abs(testcolor[0][1] - testcolor[1][1]);
      coldiffblue = abs(testcolor[0][2] - testcolor[1][2]);
      coldiffmax = coldiffred;
      if (coldiffmax < coldiffgreen) coldiffmax = coldiffgreen;
      if (coldiffmax < coldiffblue) coldiffmax = coldiffblue;
      if (coldiffmax > 0) {
         if (coldiffmax > 4) factor = 2;
         else if (coldiffmax > 2) factor = 3;
         else factor = 4;
         /* Won't do much if the color value is near 255... */
         /* argh so many ifs */
         if (testcolor[1][1] >= testcolor[0][1]) {
            ind1 = 1; ind0 = 0;
         }
         else {
            ind1 = 0; ind0 = 1;
         }
         if ((testcolor[ind1][1] + factor * coldiffgreen) <= 255)
            testcolor[ind1][1] += factor * coldiffgreen;
         else testcolor[ind1][1] = 255;
         if ((testcolor[ind1][0] - testcolor[ind0][1]) > 0) {
            if ((testcolor[ind1][0] + factor * coldiffred) <= 255)
               testcolor[ind1][0] += factor * coldiffred;
            else testcolor[ind1][0] = 255;
         }
         else {
            if ((testcolor[ind0][0] + factor * coldiffred) <= 255)
               testcolor[ind0][0] += factor * coldiffred;
            else testcolor[ind0][0] = 255;
         }
         if ((testcolor[ind1][2] - testcolor[ind0][2]) > 0) {
            if ((testcolor[ind1][2] + factor * coldiffblue) <= 255)
               testcolor[ind1][2] += factor * coldiffblue;
            else testcolor[ind1][2] = 255;
         }
         else {
            if ((testcolor[ind0][2] + factor * coldiffblue) <= 255)
               testcolor[ind0][2] += factor * coldiffblue;
            else testcolor[ind0][2] = 255;
         }
      }
   }

   if (((testcolor[0][0] & 0xf8) << 8 | (testcolor[0][1] & 0xfc) << 3 | testcolor[0][2] >> 3) <
      ((testcolor[1][0] & 0xf8) << 8 | (testcolor[1][1] & 0xfc) << 3 | testcolor[1][2]) >> 3) {
      for (i = 0; i < 3; i++) {
         bestcolor[0][i] = testcolor[0][i];
         bestcolor[1][i] = testcolor[1][i];
      }
   }
   else {
      for (i = 0; i < 3; i++) {
         bestcolor[0][i] = testcolor[1][i];
         bestcolor[1][i] = testcolor[0][i];
      }
   }

/*     fprintf(stderr, "color end 0 r/g/b %d/%d/%d, 1 r/g/b %d/%d/%d\n",
     bestcolor[0][0], bestcolor[0][1], bestcolor[0][2], bestcolor[1][0], bestcolor[1][1], bestcolor[1][2]);*/
}