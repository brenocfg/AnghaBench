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
struct gl_texture_object {int dummy; } ;
struct gl_texture_image {scalar_t__ Width; scalar_t__ Height; int Format; int /*<<< orphan*/ * Data; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
#define  GL_ALPHA 134 
#define  GL_COLOR_INDEX 133 
#define  GL_INTENSITY 132 
#define  GL_LUMINANCE 131 
#define  GL_LUMINANCE_ALPHA 130 
#define  GL_RGB 129 
#define  GL_RGBA 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  gl_problem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  palette_sample (struct gl_texture_object const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_2d_texel( const struct gl_texture_object *tObj,
                          const struct gl_texture_image *img, GLint i, GLint j,
                          GLubyte *red, GLubyte *green, GLubyte *blue,
                          GLubyte *alpha )
{
   GLint width = img->Width;    /* includes border */
   GLubyte *texel;

#ifdef DEBUG
   GLint height = img->Height;  /* includes border */
   if (i<0 || i>=width)  abort();
   if (j<0 || j>=height)  abort();
#endif

   switch (img->Format) {
      case GL_COLOR_INDEX:
         {
            GLubyte index = img->Data[ width *j + i ];
            palette_sample(tObj, index, red, green, blue, alpha);
            return;
         }
      case GL_ALPHA:
         *alpha = img->Data[ width * j + i ];
         return;
      case GL_LUMINANCE:
      case GL_INTENSITY:
         *red   = img->Data[ width * j + i ];
         return;
      case GL_LUMINANCE_ALPHA:
         texel = img->Data + (width * j + i) * 2;
         *red   = texel[0];
         *alpha = texel[1];
         return;
      case GL_RGB:
         texel = img->Data + (width * j + i) * 3;
         *red   = texel[0];
         *green = texel[1];
         *blue  = texel[2];
         return;
      case GL_RGBA:
         texel = img->Data + (width * j + i) * 4;
         *red   = texel[0];
         *green = texel[1];
         *blue  = texel[2];
         *alpha = texel[3];
         return;
      default:
         gl_problem(NULL, "Bad format in get_2d_texel");
   }
}