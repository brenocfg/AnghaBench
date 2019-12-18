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
struct vertex_buffer {double** Win; double** Clip; double** TexCoord; scalar_t__* Index; scalar_t__** Color; } ;
struct TYPE_7__ {scalar_t__ StippleCounter; TYPE_1__* Visual; struct vertex_buffer* VB; } ;
struct TYPE_6__ {double InvRedScale; double InvGreenScale; double InvBlueScale; double InvAlphaScale; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLint ;
typedef  double GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 double DEPTH_SCALE ; 
 int /*<<< orphan*/  FEEDBACK_TOKEN (TYPE_2__*,double) ; 
 scalar_t__ GL_LINE_RESET_TOKEN ; 
 scalar_t__ GL_LINE_TOKEN ; 
 int /*<<< orphan*/  gl_feedback_vertex (TYPE_2__*,double,double,double,double,double*,double,double*) ; 

__attribute__((used)) static void feedback_line( GLcontext *ctx, GLuint v1, GLuint v2, GLuint pv )
{
   struct vertex_buffer *VB = ctx->VB;
   GLfloat x1, y1, z1, w1;
   GLfloat x2, y2, z2, w2;
   GLfloat tex1[4], tex2[4], invq;
   GLfloat invRedScale   = ctx->Visual->InvRedScale;
   GLfloat invGreenScale = ctx->Visual->InvGreenScale;
   GLfloat invBlueScale  = ctx->Visual->InvBlueScale;
   GLfloat invAlphaScale = ctx->Visual->InvAlphaScale;

   x1 = VB->Win[v1][0];
   y1 = VB->Win[v1][1];
   z1 = VB->Win[v1][2] / DEPTH_SCALE;
   w1 = VB->Clip[v1][3];

   x2 = VB->Win[v2][0];
   y2 = VB->Win[v2][1];
   z2 = VB->Win[v2][2] / DEPTH_SCALE;
   w2 = VB->Clip[v2][3];

   invq = (VB->TexCoord[v1][3]==0.0) ? 1.0 : (1.0F / VB->TexCoord[v1][3]);
   tex1[0] = VB->TexCoord[v1][0] * invq;
   tex1[1] = VB->TexCoord[v1][1] * invq;
   tex1[2] = VB->TexCoord[v1][2] * invq;
   tex1[3] = VB->TexCoord[v1][3];
   invq = (VB->TexCoord[v2][3]==0.0) ? 1.0 : (1.0F / VB->TexCoord[v2][3]);
   tex2[0] = VB->TexCoord[v2][0] * invq;
   tex2[1] = VB->TexCoord[v2][1] * invq;
   tex2[2] = VB->TexCoord[v2][2] * invq;
   tex2[3] = VB->TexCoord[v2][3];

   if (ctx->StippleCounter==0) {
      FEEDBACK_TOKEN( ctx, (GLfloat) (GLint) GL_LINE_RESET_TOKEN );
   }
   else {
      FEEDBACK_TOKEN( ctx, (GLfloat) (GLint) GL_LINE_TOKEN );
   }

   {
      GLfloat color[4];
      /* convert color from integer to a float in [0,1] */
      color[0] = (GLfloat) VB->Color[pv][0] * invRedScale;
      color[1] = (GLfloat) VB->Color[pv][1] * invGreenScale;
      color[2] = (GLfloat) VB->Color[pv][2] * invBlueScale;
      color[3] = (GLfloat) VB->Color[pv][3] * invAlphaScale;
      gl_feedback_vertex( ctx, x1,y1,z1,w1, color,
                          (GLfloat) VB->Index[pv], tex1 );
      gl_feedback_vertex( ctx, x2,y2,z2,w2, color,
                          (GLfloat) VB->Index[pv], tex2 );
   }

   ctx->StippleCounter++;
}