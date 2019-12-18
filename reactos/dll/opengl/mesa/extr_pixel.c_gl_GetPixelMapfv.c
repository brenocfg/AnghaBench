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
struct TYPE_6__ {size_t MapItoIsize; size_t MapStoSsize; int MapItoRsize; int MapItoGsize; int MapItoBsize; int MapItoAsize; int MapRtoRsize; int MapGtoGsize; int MapBtoBsize; int MapAtoAsize; int /*<<< orphan*/  MapAtoA; int /*<<< orphan*/  MapBtoB; int /*<<< orphan*/  MapGtoG; int /*<<< orphan*/  MapRtoR; int /*<<< orphan*/  MapItoA; int /*<<< orphan*/  MapItoB; int /*<<< orphan*/  MapItoG; int /*<<< orphan*/  MapItoR; int /*<<< orphan*/ * MapStoS; int /*<<< orphan*/ * MapItoI; } ;
struct TYPE_7__ {TYPE_1__ Pixel; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_PIXEL_MAP_A_TO_A 137 
#define  GL_PIXEL_MAP_B_TO_B 136 
#define  GL_PIXEL_MAP_G_TO_G 135 
#define  GL_PIXEL_MAP_I_TO_A 134 
#define  GL_PIXEL_MAP_I_TO_B 133 
#define  GL_PIXEL_MAP_I_TO_G 132 
#define  GL_PIXEL_MAP_I_TO_I 131 
#define  GL_PIXEL_MAP_I_TO_R 130 
#define  GL_PIXEL_MAP_R_TO_R 129 
#define  GL_PIXEL_MAP_S_TO_S 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetPixelMapfv( GLcontext *ctx, GLenum map, GLfloat *values )
{
   GLuint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetPixelMapfv" );
      return;
   }
   switch (map) {
      case GL_PIXEL_MAP_I_TO_I:
         for (i=0;i<ctx->Pixel.MapItoIsize;i++) {
	    values[i] = (GLfloat) ctx->Pixel.MapItoI[i];
	 }
	 break;
      case GL_PIXEL_MAP_S_TO_S:
         for (i=0;i<ctx->Pixel.MapStoSsize;i++) {
	    values[i] = (GLfloat) ctx->Pixel.MapStoS[i];
	 }
	 break;
      case GL_PIXEL_MAP_I_TO_R:
         MEMCPY(values,ctx->Pixel.MapItoR,ctx->Pixel.MapItoRsize*sizeof(GLfloat));
	 break;
      case GL_PIXEL_MAP_I_TO_G:
         MEMCPY(values,ctx->Pixel.MapItoG,ctx->Pixel.MapItoGsize*sizeof(GLfloat));
	 break;
      case GL_PIXEL_MAP_I_TO_B:
         MEMCPY(values,ctx->Pixel.MapItoB,ctx->Pixel.MapItoBsize*sizeof(GLfloat));
	 break;
      case GL_PIXEL_MAP_I_TO_A:
         MEMCPY(values,ctx->Pixel.MapItoA,ctx->Pixel.MapItoAsize*sizeof(GLfloat));
	 break;
      case GL_PIXEL_MAP_R_TO_R:
         MEMCPY(values,ctx->Pixel.MapRtoR,ctx->Pixel.MapRtoRsize*sizeof(GLfloat));
	 break;
      case GL_PIXEL_MAP_G_TO_G:
         MEMCPY(values,ctx->Pixel.MapGtoG,ctx->Pixel.MapGtoGsize*sizeof(GLfloat));
	 break;
      case GL_PIXEL_MAP_B_TO_B:
         MEMCPY(values,ctx->Pixel.MapBtoB,ctx->Pixel.MapBtoBsize*sizeof(GLfloat));
	 break;
      case GL_PIXEL_MAP_A_TO_A:
         MEMCPY(values,ctx->Pixel.MapAtoA,ctx->Pixel.MapAtoAsize*sizeof(GLfloat));
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetPixelMapfv" );
   }
}