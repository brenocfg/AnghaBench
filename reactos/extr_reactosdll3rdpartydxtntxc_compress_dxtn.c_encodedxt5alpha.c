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
typedef  size_t GLubyte ;
typedef  int GLshort ;
typedef  size_t GLint ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  writedxt5encodedalphablock (size_t*,size_t,size_t,size_t*) ; 

__attribute__((used)) static void encodedxt5alpha(GLubyte *blkaddr, GLubyte srccolors[4][4][4],
                            GLint numxpixels, GLint numypixels)
{
   GLubyte alphabase[2], alphause[2];
   GLshort alphatest[2];
   GLuint alphablockerror1, alphablockerror2, alphablockerror3;
   GLubyte i, j, aindex, acutValues[7];
   GLubyte alphaenc1[16], alphaenc2[16], alphaenc3[16];
   GLboolean alphaabsmin = GL_FALSE;
   GLboolean alphaabsmax = GL_FALSE;
   GLshort alphadist;

   /* find lowest and highest alpha value in block, alphabase[0] lowest, alphabase[1] highest */
   alphabase[0] = 0xff; alphabase[1] = 0x0;
   for (j = 0; j < numypixels; j++) {
      for (i = 0; i < numxpixels; i++) {
         if (srccolors[j][i][3] == 0)
            alphaabsmin = GL_TRUE;
         else if (srccolors[j][i][3] == 255)
            alphaabsmax = GL_TRUE;
         else {
            if (srccolors[j][i][3] > alphabase[1])
               alphabase[1] = srccolors[j][i][3];
            if (srccolors[j][i][3] < alphabase[0])
               alphabase[0] = srccolors[j][i][3];
         }
      }
   }


   if ((alphabase[0] > alphabase[1]) && !(alphaabsmin && alphaabsmax)) { /* one color, either max or min */
      /* shortcut here since it is a very common case (and also avoids later problems) */
      /* || (alphabase[0] == alphabase[1] && !alphaabsmin && !alphaabsmax) */
      /* could also thest for alpha0 == alpha1 (and not min/max), but probably not common, so don't bother */

      *blkaddr++ = srccolors[0][0][3];
      blkaddr++;
      *blkaddr++ = 0;
      *blkaddr++ = 0;
      *blkaddr++ = 0;
      *blkaddr++ = 0;
      *blkaddr++ = 0;
      *blkaddr++ = 0;
/*      fprintf(stderr, "enc0 used\n");*/
      return;
   }

   /* find best encoding for alpha0 > alpha1 */
   /* it's possible this encoding is better even if both alphaabsmin and alphaabsmax are true */
   alphablockerror1 = 0x0;
   alphablockerror2 = 0xffffffff;
   alphablockerror3 = 0xffffffff;
   if (alphaabsmin) alphause[0] = 0;
   else alphause[0] = alphabase[0];
   if (alphaabsmax) alphause[1] = 255;
   else alphause[1] = alphabase[1];
   /* calculate the 7 cut values, just the middle between 2 of the computed alpha values */
   for (aindex = 0; aindex < 7; aindex++) {
      /* don't forget here is always rounded down */
      acutValues[aindex] = (alphause[0] * (2*aindex + 1) + alphause[1] * (14 - (2*aindex + 1))) / 14;
   }

   for (j = 0; j < numypixels; j++) {
      for (i = 0; i < numxpixels; i++) {
         /* maybe it's overkill to have the most complicated calculation just for the error
            calculation which we only need to figure out if encoding1 or encoding2 is better... */
         if (srccolors[j][i][3] > acutValues[0]) {
            alphaenc1[4*j + i] = 0;
            alphadist = srccolors[j][i][3] - alphause[1];
         }
         else if (srccolors[j][i][3] > acutValues[1]) {
            alphaenc1[4*j + i] = 2;
            alphadist = srccolors[j][i][3] - (alphause[1] * 6 + alphause[0] * 1) / 7;
         }
         else if (srccolors[j][i][3] > acutValues[2]) {
            alphaenc1[4*j + i] = 3;
            alphadist = srccolors[j][i][3] - (alphause[1] * 5 + alphause[0] * 2) / 7;
         }
         else if (srccolors[j][i][3] > acutValues[3]) {
            alphaenc1[4*j + i] = 4;
            alphadist = srccolors[j][i][3] - (alphause[1] * 4 + alphause[0] * 3) / 7;
         }
         else if (srccolors[j][i][3] > acutValues[4]) {
            alphaenc1[4*j + i] = 5;
            alphadist = srccolors[j][i][3] - (alphause[1] * 3 + alphause[0] * 4) / 7;
         }
         else if (srccolors[j][i][3] > acutValues[5]) {
            alphaenc1[4*j + i] = 6;
            alphadist = srccolors[j][i][3] - (alphause[1] * 2 + alphause[0] * 5) / 7;
         }
         else if (srccolors[j][i][3] > acutValues[6]) {
            alphaenc1[4*j + i] = 7;
            alphadist = srccolors[j][i][3] - (alphause[1] * 1 + alphause[0] * 6) / 7;
         }
         else {
            alphaenc1[4*j + i] = 1;
            alphadist = srccolors[j][i][3] - alphause[0];
         }
         alphablockerror1 += alphadist * alphadist;
      }
   }
/*      for (i = 0; i < 16; i++) {
         fprintf(stderr, "%d ", alphaenc1[i]);
      }
      fprintf(stderr, "cutVals ");
      for (i = 0; i < 8; i++) {
         fprintf(stderr, "%d ", acutValues[i]);
      }
      fprintf(stderr, "srcVals ");
      for (j = 0; j < numypixels; j++)
         for (i = 0; i < numxpixels; i++) {
            fprintf(stderr, "%d ", srccolors[j][i][3]);
         }

      fprintf(stderr, "\n");
   }*/
   /* it's not very likely this encoding is better if both alphaabsmin and alphaabsmax
      are false but try it anyway */
   if (alphablockerror1 >= 32) {

      /* don't bother if encoding is already very good, this condition should also imply
      we have valid alphabase colors which we absolutely need (alphabase[0] <= alphabase[1]) */
      alphablockerror2 = 0;
      for (aindex = 0; aindex < 5; aindex++) {
         /* don't forget here is always rounded down */
         acutValues[aindex] = (alphabase[0] * (10 - (2*aindex + 1)) + alphabase[1] * (2*aindex + 1)) / 10;
      }
      for (j = 0; j < numypixels; j++) {
         for (i = 0; i < numxpixels; i++) {
             /* maybe it's overkill to have the most complicated calculation just for the error
               calculation which we only need to figure out if encoding1 or encoding2 is better... */
            if (srccolors[j][i][3] == 0) {
               alphaenc2[4*j + i] = 6;
               alphadist = 0;
            }
            else if (srccolors[j][i][3] == 255) {
               alphaenc2[4*j + i] = 7;
               alphadist = 0;
            }
            else if (srccolors[j][i][3] <= acutValues[0]) {
               alphaenc2[4*j + i] = 0;
               alphadist = srccolors[j][i][3] - alphabase[0];
            }
            else if (srccolors[j][i][3] <= acutValues[1]) {
               alphaenc2[4*j + i] = 2;
               alphadist = srccolors[j][i][3] - (alphabase[0] * 4 + alphabase[1] * 1) / 5;
            }
            else if (srccolors[j][i][3] <= acutValues[2]) {
               alphaenc2[4*j + i] = 3;
               alphadist = srccolors[j][i][3] - (alphabase[0] * 3 + alphabase[1] * 2) / 5;
            }
            else if (srccolors[j][i][3] <= acutValues[3]) {
               alphaenc2[4*j + i] = 4;
               alphadist = srccolors[j][i][3] - (alphabase[0] * 2 + alphabase[1] * 3) / 5;
            }
            else if (srccolors[j][i][3] <= acutValues[4]) {
               alphaenc2[4*j + i] = 5;
               alphadist = srccolors[j][i][3] - (alphabase[0] * 1 + alphabase[1] * 4) / 5;
            }
            else {
               alphaenc2[4*j + i] = 1;
               alphadist = srccolors[j][i][3] - alphabase[1];
            }
            alphablockerror2 += alphadist * alphadist;
         }
      }


      /* skip this if the error is already very small
         this encoding is MUCH better on average than #2 though, but expensive! */
      if ((alphablockerror2 > 96) && (alphablockerror1 > 96)) {
         GLshort blockerrlin1 = 0;
         GLshort blockerrlin2 = 0;
         GLubyte nralphainrangelow = 0;
         GLubyte nralphainrangehigh = 0;
         alphatest[0] = 0xff;
         alphatest[1] = 0x0;
         /* if we have large range it's likely there are values close to 0/255, try to map them to 0/255 */
         for (j = 0; j < numypixels; j++) {
            for (i = 0; i < numxpixels; i++) {
               if ((srccolors[j][i][3] > alphatest[1]) && (srccolors[j][i][3] < (255 -(alphabase[1] - alphabase[0]) / 28)))
                  alphatest[1] = srccolors[j][i][3];
               if ((srccolors[j][i][3] < alphatest[0]) && (srccolors[j][i][3] > (alphabase[1] - alphabase[0]) / 28))
                  alphatest[0] = srccolors[j][i][3];
            }
         }
          /* shouldn't happen too often, don't really care about those degenerated cases */
          if (alphatest[1] <= alphatest[0]) {
             alphatest[0] = 1;
             alphatest[1] = 254;
/*             fprintf(stderr, "only 1 or 0 colors for encoding!\n");*/
         }
         for (aindex = 0; aindex < 5; aindex++) {
         /* don't forget here is always rounded down */
            acutValues[aindex] = (alphatest[0] * (10 - (2*aindex + 1)) + alphatest[1] * (2*aindex + 1)) / 10;
         }

         /* find the "average" difference between the alpha values and the next encoded value.
            This is then used to calculate new base values.
            Should there be some weighting, i.e. those values closer to alphatest[x] have more weight,
            since they will see more improvement, and also because the values in the middle are somewhat
            likely to get no improvement at all (because the base values might move in different directions)?
            OTOH it would mean the values in the middle are even less likely to get an improvement
         */
         for (j = 0; j < numypixels; j++) {
            for (i = 0; i < numxpixels; i++) {
               if (srccolors[j][i][3] <= alphatest[0] / 2) {
               }
               else if (srccolors[j][i][3] > ((255 + alphatest[1]) / 2)) {
               }
               else if (srccolors[j][i][3] <= acutValues[0]) {
                  blockerrlin1 += (srccolors[j][i][3] - alphatest[0]);
                  nralphainrangelow += 1;
               }
               else if (srccolors[j][i][3] <= acutValues[1]) {
                  blockerrlin1 += (srccolors[j][i][3] - (alphatest[0] * 4 + alphatest[1] * 1) / 5);
                  blockerrlin2 += (srccolors[j][i][3] - (alphatest[0] * 4 + alphatest[1] * 1) / 5);
                  nralphainrangelow += 1;
                  nralphainrangehigh += 1;
               }
               else if (srccolors[j][i][3] <= acutValues[2]) {
                  blockerrlin1 += (srccolors[j][i][3] - (alphatest[0] * 3 + alphatest[1] * 2) / 5);
                  blockerrlin2 += (srccolors[j][i][3] - (alphatest[0] * 3 + alphatest[1] * 2) / 5);
                  nralphainrangelow += 1;
                  nralphainrangehigh += 1;
               }
               else if (srccolors[j][i][3] <= acutValues[3]) {
                  blockerrlin1 += (srccolors[j][i][3] - (alphatest[0] * 2 + alphatest[1] * 3) / 5);
                  blockerrlin2 += (srccolors[j][i][3] - (alphatest[0] * 2 + alphatest[1] * 3) / 5);
                  nralphainrangelow += 1;
                  nralphainrangehigh += 1;
               }
               else if (srccolors[j][i][3] <= acutValues[4]) {
                  blockerrlin1 += (srccolors[j][i][3] - (alphatest[0] * 1 + alphatest[1] * 4) / 5);
                  blockerrlin2 += (srccolors[j][i][3] - (alphatest[0] * 1 + alphatest[1] * 4) / 5);
                  nralphainrangelow += 1;
                  nralphainrangehigh += 1;
                  }
               else {
                  blockerrlin2 += (srccolors[j][i][3] - alphatest[1]);
                  nralphainrangehigh += 1;
               }
            }
         }
         /* shouldn't happen often, needed to avoid div by zero */
         if (nralphainrangelow == 0) nralphainrangelow = 1;
         if (nralphainrangehigh == 0) nralphainrangehigh = 1;
         alphatest[0] = alphatest[0] + (blockerrlin1 / nralphainrangelow);
/*         fprintf(stderr, "block err lin low %d, nr %d\n", blockerrlin1, nralphainrangelow);
         fprintf(stderr, "block err lin high %d, nr %d\n", blockerrlin2, nralphainrangehigh);*/
         /* again shouldn't really happen often... */
         if (alphatest[0] < 0) {
            alphatest[0] = 0;
/*            fprintf(stderr, "adj alpha base val to 0\n");*/
         }
         alphatest[1] = alphatest[1] + (blockerrlin2 / nralphainrangehigh);
         if (alphatest[1] > 255) {
            alphatest[1] = 255;
/*            fprintf(stderr, "adj alpha base val to 255\n");*/
         }

         alphablockerror3 = 0;
         for (aindex = 0; aindex < 5; aindex++) {
         /* don't forget here is always rounded down */
            acutValues[aindex] = (alphatest[0] * (10 - (2*aindex + 1)) + alphatest[1] * (2*aindex + 1)) / 10;
         }
         for (j = 0; j < numypixels; j++) {
            for (i = 0; i < numxpixels; i++) {
                /* maybe it's overkill to have the most complicated calculation just for the error
                  calculation which we only need to figure out if encoding1 or encoding2 is better... */
               if (srccolors[j][i][3] <= alphatest[0] / 2) {
                  alphaenc3[4*j + i] = 6;
                  alphadist = srccolors[j][i][3];
               }
               else if (srccolors[j][i][3] > ((255 + alphatest[1]) / 2)) {
                  alphaenc3[4*j + i] = 7;
                  alphadist = 255 - srccolors[j][i][3];
               }
               else if (srccolors[j][i][3] <= acutValues[0]) {
                  alphaenc3[4*j + i] = 0;
                  alphadist = srccolors[j][i][3] - alphatest[0];
               }
               else if (srccolors[j][i][3] <= acutValues[1]) {
                 alphaenc3[4*j + i] = 2;
                 alphadist = srccolors[j][i][3] - (alphatest[0] * 4 + alphatest[1] * 1) / 5;
               }
               else if (srccolors[j][i][3] <= acutValues[2]) {
                  alphaenc3[4*j + i] = 3;
                  alphadist = srccolors[j][i][3] - (alphatest[0] * 3 + alphatest[1] * 2) / 5;
               }
               else if (srccolors[j][i][3] <= acutValues[3]) {
                  alphaenc3[4*j + i] = 4;
                  alphadist = srccolors[j][i][3] - (alphatest[0] * 2 + alphatest[1] * 3) / 5;
               }
               else if (srccolors[j][i][3] <= acutValues[4]) {
                  alphaenc3[4*j + i] = 5;
                  alphadist = srccolors[j][i][3] - (alphatest[0] * 1 + alphatest[1] * 4) / 5;
               }
               else {
                  alphaenc3[4*j + i] = 1;
                  alphadist = srccolors[j][i][3] - alphatest[1];
               }
               alphablockerror3 += alphadist * alphadist;
            }
         }
      }
   }
  /* write the alpha values and encoding back. */
   if ((alphablockerror1 <= alphablockerror2) && (alphablockerror1 <= alphablockerror3)) {
/*      if (alphablockerror1 > 96) fprintf(stderr, "enc1 used, error %d\n", alphablockerror1);*/
      writedxt5encodedalphablock( blkaddr, alphause[1], alphause[0], alphaenc1 );
   }
   else if (alphablockerror2 <= alphablockerror3) {
/*      if (alphablockerror2 > 96) fprintf(stderr, "enc2 used, error %d\n", alphablockerror2);*/
      writedxt5encodedalphablock( blkaddr, alphabase[0], alphabase[1], alphaenc2 );
   }
   else {
/*      fprintf(stderr, "enc3 used, error %d\n", alphablockerror3);*/
      writedxt5encodedalphablock( blkaddr, (GLubyte)alphatest[0], (GLubyte)alphatest[1], alphaenc3 );
   }
}