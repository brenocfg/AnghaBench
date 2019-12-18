#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gl_texture_object {int PaletteIntFormat; int PaletteSize; } ;
struct TYPE_6__ {struct gl_texture_object* Current2D; struct gl_texture_object* Current1D; } ;
struct TYPE_7__ {TYPE_1__ Texture; } ;
typedef  int GLint ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_COLOR_TABLE_ALPHA_SIZE_EXT 137 
#define  GL_COLOR_TABLE_BLUE_SIZE_EXT 136 
#define  GL_COLOR_TABLE_FORMAT_EXT 135 
#define  GL_COLOR_TABLE_GREEN_SIZE_EXT 134 
#define  GL_COLOR_TABLE_INTENSITY_SIZE_EXT 133 
#define  GL_COLOR_TABLE_LUMINANCE_SIZE_EXT 132 
#define  GL_COLOR_TABLE_RED_SIZE_EXT 131 
#define  GL_COLOR_TABLE_WIDTH_EXT 130 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_TEXTURE_1D 129 
#define  GL_TEXTURE_2D 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetColorTableParameteriv( GLcontext *ctx, GLenum target,
                                  GLenum pname, GLint *params )
{
   struct gl_texture_object *texObj;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetColorTableParameter" );
      return;
   }

   switch (target) {
      case GL_TEXTURE_1D:
         texObj = ctx->Texture.Current1D;
         break;
      case GL_TEXTURE_2D:
         texObj = ctx->Texture.Current2D;
         break;
      default:
         gl_error(ctx, GL_INVALID_ENUM, "glGetColorTableParameter(target)");
         return;
   }

   switch (pname) {
      case GL_COLOR_TABLE_FORMAT_EXT:
         if (texObj)
            *params = texObj->PaletteIntFormat;
         break;
      case GL_COLOR_TABLE_WIDTH_EXT:
         if (texObj)
            *params = texObj->PaletteSize;
         break;
      case GL_COLOR_TABLE_RED_SIZE_EXT:
         *params = 8;
         break;
      case GL_COLOR_TABLE_GREEN_SIZE_EXT:
         *params = 8;
         break;
      case GL_COLOR_TABLE_BLUE_SIZE_EXT:
         *params = 8;
         break;
      case GL_COLOR_TABLE_ALPHA_SIZE_EXT:
         *params = 8;
         break;
      case GL_COLOR_TABLE_LUMINANCE_SIZE_EXT:
         *params = 8;
         break;
      case GL_COLOR_TABLE_INTENSITY_SIZE_EXT:
         *params = 8;
         break;
      default:
         gl_error(ctx, GL_INVALID_ENUM, "glGetColorTableParameter" );
         return;
   }
}