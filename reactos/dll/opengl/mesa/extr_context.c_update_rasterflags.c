#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ DrawBuffer; scalar_t__ ColorMask; scalar_t__ IndexMask; scalar_t__ SWmasking; scalar_t__ SWLogicOpEnabled; scalar_t__ BlendEnabled; scalar_t__ AlphaEnabled; } ;
struct TYPE_15__ {scalar_t__ X; scalar_t__ Width; scalar_t__ Y; scalar_t__ Height; } ;
struct TYPE_14__ {scalar_t__ Enabled; } ;
struct TYPE_13__ {scalar_t__ Enabled; } ;
struct TYPE_12__ {scalar_t__ Enabled; } ;
struct TYPE_11__ {scalar_t__ Test; } ;
struct TYPE_19__ {int /*<<< orphan*/  RasterMask; TYPE_8__ Color; TYPE_7__* Visual; TYPE_6__* Buffer; TYPE_5__ Viewport; TYPE_4__ Stencil; TYPE_3__ Scissor; TYPE_2__ Fog; TYPE_1__ Depth; } ;
struct TYPE_17__ {scalar_t__ RGBAflag; scalar_t__ BackAlphaEnabled; scalar_t__ FrontAlphaEnabled; } ;
struct TYPE_16__ {scalar_t__ Width; scalar_t__ Height; } ;
typedef  TYPE_9__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHABUF_BIT ; 
 int /*<<< orphan*/  ALPHATEST_BIT ; 
 int /*<<< orphan*/  BLEND_BIT ; 
 int /*<<< orphan*/  DEPTH_BIT ; 
 int /*<<< orphan*/  FOG_BIT ; 
 int /*<<< orphan*/  FRONT_AND_BACK_BIT ; 
 scalar_t__ GL_FRONT_AND_BACK ; 
 scalar_t__ GL_NONE ; 
 int /*<<< orphan*/  LOGIC_OP_BIT ; 
 int /*<<< orphan*/  MASKING_BIT ; 
 int /*<<< orphan*/  NO_DRAW_BIT ; 
 int /*<<< orphan*/  SCISSOR_BIT ; 
 int /*<<< orphan*/  STENCIL_BIT ; 
 int /*<<< orphan*/  WINCLIP_BIT ; 

__attribute__((used)) static void update_rasterflags( GLcontext *ctx )
{
   ctx->RasterMask = 0;

   if (ctx->Color.AlphaEnabled)		ctx->RasterMask |= ALPHATEST_BIT;
   if (ctx->Color.BlendEnabled)		ctx->RasterMask |= BLEND_BIT;
   if (ctx->Depth.Test)			ctx->RasterMask |= DEPTH_BIT;
   if (ctx->Fog.Enabled)		ctx->RasterMask |= FOG_BIT;
   if (ctx->Color.SWLogicOpEnabled)	ctx->RasterMask |= LOGIC_OP_BIT;
   if (ctx->Scissor.Enabled)		ctx->RasterMask |= SCISSOR_BIT;
   if (ctx->Stencil.Enabled)		ctx->RasterMask |= STENCIL_BIT;
   if (ctx->Color.SWmasking)		ctx->RasterMask |= MASKING_BIT;
   if (ctx->Visual->FrontAlphaEnabled)	ctx->RasterMask |= ALPHABUF_BIT;
   if (ctx->Visual->BackAlphaEnabled)	ctx->RasterMask |= ALPHABUF_BIT;

   if (   ctx->Viewport.X<0
       || ctx->Viewport.X + ctx->Viewport.Width > ctx->Buffer->Width
       || ctx->Viewport.Y<0
       || ctx->Viewport.Y + ctx->Viewport.Height > ctx->Buffer->Height) {
      ctx->RasterMask |= WINCLIP_BIT;
   }

   /* check if drawing to front and back buffers */
   if (ctx->Color.DrawBuffer==GL_FRONT_AND_BACK) {
      ctx->RasterMask |= FRONT_AND_BACK_BIT;
   }

   /* check if writing to color buffer(s) is disabled */
   if (ctx->Color.DrawBuffer==GL_NONE) {
      ctx->RasterMask |= NO_DRAW_BIT;
   }
   else if (ctx->Visual->RGBAflag && ctx->Color.ColorMask==0) {
      ctx->RasterMask |= NO_DRAW_BIT;
   }
   else if (!ctx->Visual->RGBAflag && ctx->Color.IndexMask==0) {
      ctx->RasterMask |= NO_DRAW_BIT;
   }
}