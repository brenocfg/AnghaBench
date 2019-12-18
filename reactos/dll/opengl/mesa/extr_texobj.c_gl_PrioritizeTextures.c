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
struct gl_texture_object {int /*<<< orphan*/  Priority; } ;
struct TYPE_7__ {TYPE_1__* Shared; } ;
struct TYPE_6__ {int /*<<< orphan*/  TexObjects; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLsizei ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLclampf ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (int /*<<< orphan*/  const,float,float) ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 scalar_t__ HashLookup (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_PrioritizeTextures( GLcontext *ctx,
                            GLsizei n, const GLuint *texName,
                            const GLclampf *priorities )
{
   GLuint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glAreTexturesResident" );
      return;
   }
   if (n<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glAreTexturesResident(n)" );
      return;
   }

   for (i=0;i<n;i++) {
      struct gl_texture_object *t;
      if (texName[i]>0) {
         t = (struct gl_texture_object *)
            HashLookup(ctx->Shared->TexObjects, texName[i]);
         if (t) {
            t->Priority = CLAMP( priorities[i], 0.0F, 1.0F );
         }
      }
   }
}