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
struct gl_texture_object {scalar_t__ WrapS; scalar_t__ WrapT; struct gl_texture_image** Image; } ;
struct gl_texture_image {int Width; int Height; int WidthLog2; scalar_t__ Border; scalar_t__ Format; int /*<<< orphan*/ * Data; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLint ;
typedef  int const GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ GL_REPEAT ; 
 scalar_t__ GL_RGB ; 

__attribute__((used)) static void opt_sample_rgb_2d( const struct gl_texture_object *tObj,
                               GLuint n, const GLfloat s[], const GLfloat t[],
                               const GLfloat u[], const GLfloat lamda[],
                               GLubyte red[], GLubyte green[],
                               GLubyte blue[], GLubyte alpha[] )
{
   const struct gl_texture_image *img = tObj->Image[0];
   GLfloat width = img->Width, height = img->Height;
   GLint colMask = img->Width-1, rowMask = img->Height-1;
   GLint shift = img->WidthLog2;
   GLuint k;

   ASSERT(tObj->WrapS==GL_REPEAT);
   ASSERT(tObj->WrapT==GL_REPEAT);
   ASSERT(img->Border==0);
   ASSERT(img->Format==GL_RGB);

   for (k=0;k<n;k++) {
      GLint i = (GLint) (s[k] * width) & colMask;
      GLint j = (GLint) (t[k] * height) & rowMask;
      GLint pos = (j << shift) | i;
      GLubyte *texel = img->Data + pos + pos + pos;  /* pos*3 */
      red[k]   = texel[0];
      green[k] = texel[1];
      blue[k]  = texel[2];
   }
}