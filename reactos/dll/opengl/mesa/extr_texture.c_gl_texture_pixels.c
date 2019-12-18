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
struct TYPE_10__ {TYPE_1__** Image; int /*<<< orphan*/  (* SampleFunc ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  EnvMode; TYPE_4__* Current; } ;
struct TYPE_9__ {TYPE_2__ Texture; } ;
struct TYPE_7__ {int /*<<< orphan*/  Format; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int PB_SIZE ; 
 int /*<<< orphan*/  apply_texture (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void gl_texture_pixels( GLcontext *ctx, GLuint n,
                        const GLfloat s[], const GLfloat t[],
                        const GLfloat r[], const GLfloat lambda[],
                        GLubyte red[], GLubyte green[],
                        GLubyte blue[], GLubyte alpha[] )
{
   GLubyte tred[PB_SIZE];
   GLubyte tgreen[PB_SIZE];
   GLubyte tblue[PB_SIZE];
   GLubyte talpha[PB_SIZE];

   if (!ctx->Texture.Current || !ctx->Texture.Current->SampleFunc)
      return;

   /* Sample the texture. */
   (*ctx->Texture.Current->SampleFunc)( ctx->Texture.Current, n,
                                        s, t, r, lambda,
                                        tred, tgreen, tblue, talpha );

   apply_texture( ctx, n,
                  ctx->Texture.Current->Image[0]->Format,
                  ctx->Texture.EnvMode,
                  red, green, blue, alpha,
                  tred, tgreen, tblue, talpha );
}