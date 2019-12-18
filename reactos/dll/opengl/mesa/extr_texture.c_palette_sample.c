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
struct gl_texture_object {size_t* Palette; int PaletteFormat; } ;
typedef  size_t GLubyte ;
typedef  int GLint ;

/* Variables and functions */
#define  GL_ALPHA 133 
#define  GL_INTENSITY 132 
#define  GL_LUMINANCE 131 
#define  GL_LUMINANCE_ALPHA 130 
#define  GL_RGB 129 
#define  GL_RGBA 128 
 int /*<<< orphan*/  gl_problem (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void palette_sample(const struct gl_texture_object *tObj,
                           GLubyte index, GLubyte *red, GLubyte *green,
                           GLubyte *blue, GLubyte *alpha)
{
   GLint i = index;
   const GLubyte *palette;

   palette = tObj->Palette;

   switch (tObj->PaletteFormat) {
      case GL_ALPHA:
         *alpha = tObj->Palette[index];
         return;
      case GL_LUMINANCE:
      case GL_INTENSITY:
         *red = palette[index];
         return;
      case GL_LUMINANCE_ALPHA:
         *red   = palette[(index << 1) + 0];
         *alpha = palette[(index << 1) + 1];
         return;
      case GL_RGB:
         *red   = palette[index * 3 + 0];
         *green = palette[index * 3 + 1];
         *blue  = palette[index * 3 + 2];
         return;
      case GL_RGBA:
         *red   = palette[(i << 2) + 0];
         *green = palette[(i << 2) + 1];
         *blue  = palette[(i << 2) + 2];
         *alpha = palette[(i << 2) + 3];
         return;
      default:
         gl_problem(NULL, "Bad palette format in palette_sample");
   }
}