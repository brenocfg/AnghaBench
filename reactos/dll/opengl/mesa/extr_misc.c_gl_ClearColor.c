#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* ClearColor ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int* ClearColor; } ;
struct TYPE_12__ {TYPE_3__ Driver; TYPE_2__* Visual; TYPE_1__ Color; } ;
struct TYPE_10__ {int RedScale; int GreenScale; int BlueScale; int AlphaScale; scalar_t__ RGBAflag; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_4__ GLcontext ;
typedef  int /*<<< orphan*/  GLclampf ;

/* Variables and functions */
 void* CLAMP (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gl_ClearColor( GLcontext *ctx, GLclampf red, GLclampf green,
                    GLclampf blue, GLclampf alpha )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glClearColor" );
      return;
   }

   ctx->Color.ClearColor[0] = CLAMP( red,   0.0F, 1.0F );
   ctx->Color.ClearColor[1] = CLAMP( green, 0.0F, 1.0F );
   ctx->Color.ClearColor[2] = CLAMP( blue,  0.0F, 1.0F );
   ctx->Color.ClearColor[3] = CLAMP( alpha, 0.0F, 1.0F );

   if (ctx->Visual->RGBAflag) {
      GLubyte r = (GLint) (ctx->Color.ClearColor[0] * ctx->Visual->RedScale);
      GLubyte g = (GLint) (ctx->Color.ClearColor[1] * ctx->Visual->GreenScale);
      GLubyte b = (GLint) (ctx->Color.ClearColor[2] * ctx->Visual->BlueScale);
      GLubyte a = (GLint) (ctx->Color.ClearColor[3] * ctx->Visual->AlphaScale);
      (*ctx->Driver.ClearColor)( ctx, r, g, b, a );
   }
}