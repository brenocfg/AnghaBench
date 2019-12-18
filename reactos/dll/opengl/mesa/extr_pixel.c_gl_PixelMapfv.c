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
struct TYPE_6__ {void** MapAtoA; scalar_t__ MapAtoAsize; void** MapBtoB; scalar_t__ MapBtoBsize; void** MapGtoG; scalar_t__ MapGtoGsize; void** MapRtoR; scalar_t__ MapRtoRsize; void** MapItoA; scalar_t__ MapItoAsize; void** MapItoB; scalar_t__ MapItoBsize; void** MapItoG; scalar_t__ MapItoGsize; void** MapItoR; scalar_t__ MapItoRsize; scalar_t__* MapItoI; scalar_t__ MapItoIsize; scalar_t__* MapStoS; scalar_t__ MapStoSsize; } ;
struct TYPE_7__ {TYPE_1__ Pixel; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 void* CLAMP (int /*<<< orphan*/  const,double,double) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
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
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 scalar_t__ MAX_PIXEL_MAP_TABLE ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_PixelMapfv( GLcontext *ctx,
                    GLenum map, GLint mapsize, const GLfloat *values )
{
   GLuint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPixelMapfv" );
      return;
   }

   if (mapsize<0 || mapsize>MAX_PIXEL_MAP_TABLE) {
      gl_error( ctx, GL_INVALID_VALUE, "glPixelMapfv(mapsize)" );
      return;
   }

   if (map>=GL_PIXEL_MAP_S_TO_S && map<=GL_PIXEL_MAP_I_TO_A) {
      /* test that mapsize is a power of two */
      GLuint p;
      GLboolean ok = GL_FALSE;
      for (p=1; p<=MAX_PIXEL_MAP_TABLE; p=p<<1) {
	 if ( (p&mapsize) == p ) {
	    ok = GL_TRUE;
	    break;
	 }
      }
      if (!ok) {
	 gl_error( ctx, GL_INVALID_VALUE, "glPixelMapfv(mapsize)" );
         return;
      }
   }

   switch (map) {
      case GL_PIXEL_MAP_S_TO_S:
         ctx->Pixel.MapStoSsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapStoS[i] = (GLint) values[i];
	 }
	 break;
      case GL_PIXEL_MAP_I_TO_I:
         ctx->Pixel.MapItoIsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapItoI[i] = (GLint) values[i];
	 }
	 break;
      case GL_PIXEL_MAP_I_TO_R:
         ctx->Pixel.MapItoRsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapItoR[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      case GL_PIXEL_MAP_I_TO_G:
         ctx->Pixel.MapItoGsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapItoG[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      case GL_PIXEL_MAP_I_TO_B:
         ctx->Pixel.MapItoBsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapItoB[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      case GL_PIXEL_MAP_I_TO_A:
         ctx->Pixel.MapItoAsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapItoA[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      case GL_PIXEL_MAP_R_TO_R:
         ctx->Pixel.MapRtoRsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapRtoR[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      case GL_PIXEL_MAP_G_TO_G:
         ctx->Pixel.MapGtoGsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapGtoG[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      case GL_PIXEL_MAP_B_TO_B:
         ctx->Pixel.MapBtoBsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapBtoB[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      case GL_PIXEL_MAP_A_TO_A:
         ctx->Pixel.MapAtoAsize = mapsize;
         for (i=0;i<mapsize;i++) {
	    ctx->Pixel.MapAtoA[i] = CLAMP( values[i], 0.0, 1.0 );
	 }
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glPixelMapfv(map)" );
   }
}