#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float* Color; float End; int Mode; float Start; float Density; } ;
struct TYPE_8__ {TYPE_2__ Fog; TYPE_1__* Visual; } ;
struct TYPE_6__ {float RedScale; float GreenScale; float BlueScale; } ;
typedef  size_t GLuint ;
typedef  float GLubyte ;
typedef  float GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 float ABSF (float) ; 
 float CLAMP (float,float,float) ; 
#define  GL_EXP 130 
#define  GL_EXP2 129 
#define  GL_LINEAR 128 
 float exp (float) ; 
 int /*<<< orphan*/  gl_problem (TYPE_3__*,char*) ; 

void gl_fog_color_vertices( GLcontext *ctx,
                            GLuint n, GLfloat v[][4], GLubyte color[][4] )
{
   GLuint i;
   GLfloat d;
   GLfloat fogr = ctx->Fog.Color[0] * ctx->Visual->RedScale;
   GLfloat fogg = ctx->Fog.Color[1] * ctx->Visual->GreenScale;
   GLfloat fogb = ctx->Fog.Color[2] * ctx->Visual->BlueScale;
   GLfloat end = ctx->Fog.End;

   switch (ctx->Fog.Mode) {
      case GL_LINEAR:
         d = 1.0F / (ctx->Fog.End - ctx->Fog.Start);
         for (i=0;i<n;i++) {
            GLfloat f = (end - ABSF(v[i][2])) * d;
            f = CLAMP( f, 0.0F, 1.0F );
            color[i][0] = f * color[i][0] + (1.0F-f) * fogr;
            color[i][1] = f * color[i][1] + (1.0F-f) * fogg;
            color[i][2] = f * color[i][2] + (1.0F-f) * fogb;
         }
	 break;
      case GL_EXP:
         d = -ctx->Fog.Density;
         for (i=0;i<n;i++) {
            GLfloat f = exp( d * ABSF(v[i][2]) );
            f = CLAMP( f, 0.0F, 1.0F );
            color[i][0] = f * color[i][0] + (1.0F-f) * fogr;
            color[i][1] = f * color[i][1] + (1.0F-f) * fogg;
            color[i][2] = f * color[i][2] + (1.0F-f) * fogb;
         }
	 break;
      case GL_EXP2:
         d = -(ctx->Fog.Density*ctx->Fog.Density);
         for (i=0;i<n;i++) {
            GLfloat z = ABSF(v[i][2]);
            GLfloat f = exp( d * z*z );
            f = CLAMP( f, 0.0F, 1.0F );
            color[i][0] = f * color[i][0] + (1.0F-f) * fogr;
            color[i][1] = f * color[i][1] + (1.0F-f) * fogg;
            color[i][2] = f * color[i][2] + (1.0F-f) * fogb;
         }
	 break;
      default:
         gl_problem(ctx, "Bad fog mode in gl_fog_color_vertices");
         return;
   }
}