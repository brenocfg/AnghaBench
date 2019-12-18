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
typedef  int GLint ;
typedef  double GLfloat ;

/* Variables and functions */
 int BOX2 ; 
 double __GLU_SWAP_4_BYTES (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void halve1Dimage_float(GLint components, GLuint width, GLuint height,
			       const GLfloat *dataIn, GLfloat *dataOut,
			       GLint element_size, GLint ysize,
			       GLint group_size, GLint myswap_bytes)
{
   GLint halfWidth= width / 2;
   GLint halfHeight= height / 2;
   const char *src= (const char *) dataIn;
   GLfloat *dest= dataOut;
   int jj;

   assert(width == 1 || height == 1); /* must be 1D */
   assert(width != height);	/* can't be square */

   if (height == 1) {		/* 1 row */
      assert(width != 1);	/* widthxheight can't be 1x1 */
      halfHeight= 1;

      for (jj= 0; jj< halfWidth; jj++) {
	 int kk;
	 for (kk= 0; kk< components; kk++) {
#define BOX2 2
	    GLfloat sfloat[BOX2];
	    if (myswap_bytes) {
	       sfloat[0]= __GLU_SWAP_4_BYTES(src);
	       sfloat[1]= __GLU_SWAP_4_BYTES(src+group_size);
	    }
	    else {
	       sfloat[0]= *(const GLfloat*)src;
	       sfloat[1]= *(const GLfloat*)(src+group_size);
	    }

	    *dest= (sfloat[0] + sfloat[1]) / 2.0;
	    src+= element_size;
	    dest++;
	 }
	 src+= group_size;	/* skip to next 2 */
      }
      {
	 int padBytes= ysize - (width*group_size);
	 src+= padBytes;	/* for assertion only */
      }
   }
   else if (width == 1) {	/* 1 column */
      int padBytes= ysize - (width * group_size);
      assert(height != 1);	/* widthxheight can't be 1x1 */
      halfWidth= 1;
      /* one vertical column with possible pad bytes per row */
      /* average two at a time */

      for (jj= 0; jj< halfHeight; jj++) {
	 int kk;
	 for (kk= 0; kk< components; kk++) {
#define BOX2 2
	    GLfloat sfloat[BOX2];
	    if (myswap_bytes) {
	       sfloat[0]= __GLU_SWAP_4_BYTES(src);
	       sfloat[1]= __GLU_SWAP_4_BYTES(src+ysize);
	    }
	    else {
	       sfloat[0]= *(const GLfloat*)src;
	       sfloat[1]= *(const GLfloat*)(src+ysize);
	    }
	    *dest= (sfloat[0] + sfloat[1]) / 2.0;

	    src+= element_size;
	    dest++;
	 }
	 src+= padBytes; /* add pad bytes, if any, to get to end to row */
	 src+= ysize;		/* skip to odd row */
      }
   }

   assert(src == &((const char *)dataIn)[ysize*height]);
   assert((char *)dest == &((char *)dataOut)
	  [components * element_size * halfWidth * halfHeight]);
}