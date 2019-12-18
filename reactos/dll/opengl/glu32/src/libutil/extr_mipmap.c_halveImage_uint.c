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
typedef  int GLdouble ;

/* Variables and functions */
 scalar_t__ __GLU_SWAP_4_BYTES (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  halve1Dimage_uint (int,int,int,int const*,int*,int,int,int,int) ; 

__attribute__((used)) static void halveImage_uint(GLint components, GLuint width, GLuint height,
			const GLuint *datain, GLuint *dataout,
			GLint element_size, GLint ysize, GLint group_size,
			GLint myswap_bytes)
{
    int i, j, k;
    int newwidth, newheight;
    int padBytes;
    GLuint *s;
    const char *t;

    /* handle case where there is only 1 column/row */
    if (width == 1 || height == 1) {
       assert( !(width == 1 && height == 1) ); /* can't be 1x1 */
       halve1Dimage_uint(components,width,height,datain,dataout,
			 element_size,ysize,group_size, myswap_bytes);
       return;
    }

    newwidth = width / 2;
    newheight = height / 2;
    padBytes = ysize - (width*group_size);
    s = dataout;
    t = (const char *)datain;

    /* Piece o' cake! */
    if (!myswap_bytes)
    for (i = 0; i < newheight; i++) {
	for (j = 0; j < newwidth; j++) {
	    for (k = 0; k < components; k++) {
		/* need to cast to double to hold large unsigned ints */
		s[0] = ((double)*(const GLuint*)t +
			(double)*(const GLuint*)(t+group_size) +
			(double)*(const GLuint*)(t+ysize) +
			(double)*(const GLuint*)(t+ysize+group_size))/4 + 0.5;
		s++; t += element_size;

	    }
	    t += group_size;
	}
	t += padBytes;
	t += ysize;
    }
    else
    for (i = 0; i < newheight; i++) {
	for (j = 0; j < newwidth; j++) {
	    for (k = 0; k < components; k++) {
		/* need to cast to double to hold large unsigned ints */
		GLdouble buf;
		buf = (GLdouble)__GLU_SWAP_4_BYTES(t) +
		      (GLdouble)__GLU_SWAP_4_BYTES(t+group_size) +
		      (GLdouble)__GLU_SWAP_4_BYTES(t+ysize) +
		      (GLdouble)__GLU_SWAP_4_BYTES(t+ysize+group_size);
		s[0] = (GLuint)(buf/4 + 0.5);

		s++; t += element_size;
	    }
	    t += group_size;
	}
	t += padBytes;
	t += ysize;
    }
}