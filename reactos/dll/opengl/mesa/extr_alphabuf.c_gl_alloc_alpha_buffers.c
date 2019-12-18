#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ DrawBuffer; } ;
struct TYPE_10__ {TYPE_3__* Buffer; TYPE_2__ Color; TYPE_1__* Visual; } ;
struct TYPE_9__ {int Width; int Height; int /*<<< orphan*/ * BackAlpha; int /*<<< orphan*/ * Alpha; int /*<<< orphan*/ * FrontAlpha; } ;
struct TYPE_7__ {scalar_t__ BackAlphaEnabled; scalar_t__ FrontAlphaEnabled; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLint ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_BACK ; 
 scalar_t__ GL_FRONT ; 
 int /*<<< orphan*/  GL_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 

void gl_alloc_alpha_buffers( GLcontext* ctx )
{
   GLint bytes = ctx->Buffer->Width * ctx->Buffer->Height * sizeof(GLubyte);

   if (ctx->Visual->FrontAlphaEnabled) {
      if (ctx->Buffer->FrontAlpha) {
         free( ctx->Buffer->FrontAlpha );
      }
      ctx->Buffer->FrontAlpha = (GLubyte *) malloc( bytes );
      if (!ctx->Buffer->FrontAlpha) {
         /* out of memory */
         gl_error( ctx, GL_OUT_OF_MEMORY, "Couldn't allocate front alpha buffer" );
      }
   }
   if (ctx->Visual->BackAlphaEnabled) {
      if (ctx->Buffer->BackAlpha) {
         free( ctx->Buffer->BackAlpha );
      }
      ctx->Buffer->BackAlpha = (GLubyte *) malloc( bytes );
      if (!ctx->Buffer->BackAlpha) {
         /* out of memory */
         gl_error( ctx, GL_OUT_OF_MEMORY, "Couldn't allocate back alpha buffer" );
      }
   }
   if (ctx->Color.DrawBuffer==GL_FRONT) {
      ctx->Buffer->Alpha = ctx->Buffer->FrontAlpha;
   }
   if (ctx->Color.DrawBuffer==GL_BACK) {
      ctx->Buffer->Alpha = ctx->Buffer->BackAlpha;
   }
}