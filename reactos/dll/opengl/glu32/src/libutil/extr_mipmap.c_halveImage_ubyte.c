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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  halve1Dimage_ubyte (int,int,int,int const*,int*,int,int,int) ; 

__attribute__((used)) static void halveImage_ubyte(GLint components, GLuint width, GLuint height,
			const GLubyte *datain, GLubyte *dataout,
			GLint element_size, GLint ysize, GLint group_size)
{
    int i, j, k;
    int newwidth, newheight;
    int padBytes;
    GLubyte *s;
    const char *t;

    /* handle case where there is only 1 column/row */
    if (width == 1 || height == 1) {
       assert( !(width == 1 && height == 1) ); /* can't be 1x1 */
       halve1Dimage_ubyte(components,width,height,datain,dataout,
			  element_size,ysize,group_size);
       return;
    }

    newwidth = width / 2;
    newheight = height / 2;
    padBytes = ysize - (width*group_size);
    s = dataout;
    t = (const char *)datain;

    /* Piece o' cake! */
    for (i = 0; i < newheight; i++) {
	for (j = 0; j < newwidth; j++) {
	    for (k = 0; k < components; k++) {
		s[0] = (*(const GLubyte*)t +
			*(const GLubyte*)(t+group_size) +
			*(const GLubyte*)(t+ysize) +
			*(const GLubyte*)(t+ysize+group_size) + 2) / 4;
		s++; t += element_size;
	    }
	    t += group_size;
	}
	t += padBytes;
	t += ysize;
    }
}