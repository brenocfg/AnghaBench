#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float Sx; float Tx; float Sy; float Ty; float Sz; float Tz; } ;
struct TYPE_7__ {scalar_t__ ProjectionMatrixType; scalar_t__ ModelViewMatrixType; TYPE_2__* VB; TYPE_1__ Viewport; } ;
struct TYPE_6__ {int VertexSizeMask; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  float GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 scalar_t__ MATRIX_GENERAL ; 
 scalar_t__ MATRIX_IDENTITY ; 
 scalar_t__ MATRIX_ORTHO ; 
 int /*<<< orphan*/  TRACE (char*,float,float,float,float,float,float,float) ; 
 int VERTEX4_BIT ; 

__attribute__((used)) static void viewport_map_vertices( GLcontext *ctx,
                                   GLuint n, /*const*/ GLfloat vClip[][4],
                                   const GLubyte clipMask[], GLfloat vWin[][3])
{
   GLfloat sx = ctx->Viewport.Sx;
   GLfloat tx = ctx->Viewport.Tx;
   GLfloat sy = ctx->Viewport.Sy;
   GLfloat ty = ctx->Viewport.Ty;
   GLfloat sz = ctx->Viewport.Sz;
   GLfloat tz = ctx->Viewport.Tz;

   if ((ctx->ProjectionMatrixType==MATRIX_ORTHO || 
        ctx->ProjectionMatrixType==MATRIX_IDENTITY)
       && ctx->ModelViewMatrixType!=MATRIX_GENERAL
       && (ctx->VB->VertexSizeMask & VERTEX4_BIT)==0) {
      /* don't need to divide by W */
      if (clipMask) {
         /* one or more vertices are clipped */
         GLuint i;
         for (i=0;i<n;i++) {
            if (clipMask[i]==0) {
               vWin[i][0] = vClip[i][0] * sx + tx;
               vWin[i][1] = vClip[i][1] * sy + ty;
               vWin[i][2] = vClip[i][2] * sz + tz;
            }
         }
      }
      else {
         /* no vertices are clipped */
         GLuint i;
         for (i=0;i<n;i++) {
            vWin[i][0] = vClip[i][0] * sx + tx;
            vWin[i][1] = vClip[i][1] * sy + ty;
            vWin[i][2] = vClip[i][2] * sz + tz;
         }
      }
   }
   else {
      /* need to divide by W */
      if (clipMask) {
         /* one or more vertices are clipped */
         GLuint i;
         for (i=0;i<n;i++) {
            if (clipMask[i] == 0) {
               if (vClip[i][3] != 0.0F) {
                  GLfloat wInv = 1.0F / vClip[i][3];
                  vWin[i][0] = vClip[i][0] * wInv * sx + tx;
                  vWin[i][1] = vClip[i][1] * wInv * sy + ty;
                  vWin[i][2] = vClip[i][2] * wInv * sz + tz;
               }
               else {
                  /* Div by zero!  Can't set window coords to infinity, so...*/
                  vWin[i][0] = 0.0F;
                  vWin[i][1] = 0.0F;
                  vWin[i][2] = 0.0F;
               }
            }
         }
      }
      else {
         /* no vertices are clipped */
         GLuint i;
         for (i=0;i<n;i++) {
            if (vClip[i][3] != 0.0F) {
               GLfloat wInv = 1.0F / vClip[i][3];
               vWin[i][0] = vClip[i][0] * wInv * sx + tx;
               vWin[i][1] = vClip[i][1] * wInv * sy + ty;
               vWin[i][2] = vClip[i][2] * wInv * sz + tz;
            }
            else {
               /* Divide by zero!  Can't set window coords to infinity, so...*/
               vWin[i][0] = 0.0F;
               vWin[i][1] = 0.0F;
               vWin[i][2] = 0.0F;
            }
         }
      }
   }
   if (1)
   {
       GLuint i;
       for (i = 0; i < n; i++)
       {
           TRACE("(%3.1f, %3.1f, %3.1f, %3.1f) --> (%3.1f, %3.1f, %3.1f)\n",
                   vClip[i][0], vClip[i][1], vClip[i][2], vClip[i][3],
                   vWin[i][0], vWin[i][1], vWin[i][2]);
       }
   }
}