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
struct TYPE_9__ {int /*<<< orphan*/  Clear; } ;
struct TYPE_8__ {scalar_t__ Enabled; } ;
struct TYPE_11__ {TYPE_4__* Buffer; TYPE_3__ Stencil; TYPE_2__ Scissor; TYPE_1__* Visual; } ;
struct TYPE_10__ {scalar_t__ Xmax; scalar_t__ Xmin; scalar_t__ Ymin; scalar_t__ Ymax; int Width; int Height; int /*<<< orphan*/ * Stencil; } ;
struct TYPE_7__ {scalar_t__ StencilBits; } ;
typedef  int /*<<< orphan*/  GLstencil ;
typedef  scalar_t__ GLint ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  MEMSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * STENCIL_ADDRESS (scalar_t__,scalar_t__) ; 

void gl_clear_stencil_buffer( GLcontext *ctx )
{
   if (ctx->Visual->StencilBits==0 || !ctx->Buffer->Stencil) {
      /* no stencil buffer */
      return;
   }

   if (ctx->Scissor.Enabled) {
      /* clear scissor region only */
      GLint y;
      GLint width = ctx->Buffer->Xmax - ctx->Buffer->Xmin + 1;
      for (y=ctx->Buffer->Ymin; y<=ctx->Buffer->Ymax; y++) {
         GLstencil *ptr = STENCIL_ADDRESS( ctx->Buffer->Xmin, y );
         MEMSET( ptr, ctx->Stencil.Clear, width * sizeof(GLstencil) );
      }
   }
   else {
      /* clear whole stencil buffer */
      MEMSET( ctx->Buffer->Stencil, ctx->Stencil.Clear,
              ctx->Buffer->Width * ctx->Buffer->Height * sizeof(GLstencil) );
   }
}