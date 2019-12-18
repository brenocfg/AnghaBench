#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int Height; int Width; scalar_t__ Enabled; } ;
struct TYPE_7__ {scalar_t__ DrawBuffer; int* ClearColor; } ;
struct TYPE_11__ {TYPE_4__* Buffer; TYPE_3__ Scissor; TYPE_2__* Visual; TYPE_1__ Color; } ;
struct TYPE_10__ {int* FrontAlpha; int* BackAlpha; int Ymin; int Width; int Height; int /*<<< orphan*/  Xmin; } ;
struct TYPE_8__ {int AlphaScale; scalar_t__ BackAlphaEnabled; scalar_t__ FrontAlphaEnabled; } ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
 int* ALPHA_ADDR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GL_BACK ; 
 scalar_t__ GL_FRONT ; 
 scalar_t__ GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  MEMSET (int*,int,int) ; 

void gl_clear_alpha_buffers( GLcontext* ctx )
{
   GLint buffer;

   /* Loop over front and back buffers */
   for (buffer=0;buffer<2;buffer++) {

      /* Get pointer to front or back buffer */
      GLubyte *abuffer = NULL;
      if (buffer==0
          && (   ctx->Color.DrawBuffer==GL_FRONT
              || ctx->Color.DrawBuffer==GL_FRONT_AND_BACK)
          && ctx->Visual->FrontAlphaEnabled && ctx->Buffer->FrontAlpha) {
         abuffer = ctx->Buffer->FrontAlpha;
      }
      else if (buffer==1
               && (   ctx->Color.DrawBuffer==GL_BACK
                   || ctx->Color.DrawBuffer==GL_FRONT_AND_BACK)
               && ctx->Visual->BackAlphaEnabled && ctx->Buffer->BackAlpha) {
         abuffer = ctx->Buffer->BackAlpha;
      }

      /* Clear the alpha buffer */
      if (abuffer) {
         GLubyte aclear = (GLint) (ctx->Color.ClearColor[3]
                                   * ctx->Visual->AlphaScale);
         if (ctx->Scissor.Enabled) {
            /* clear scissor region */
            GLint i, j;
            for (j=0;j<ctx->Scissor.Height;j++) {
               GLubyte *aptr = ALPHA_ADDR(ctx->Buffer->Xmin,
                                          ctx->Buffer->Ymin+j);
               for (i=0;i<ctx->Scissor.Width;i++) {
                  *aptr++ = aclear;
               }
            }
         }
         else {
            /* clear whole buffer */
            MEMSET( abuffer, aclear, ctx->Buffer->Width*ctx->Buffer->Height );
         }
      }
   }
}