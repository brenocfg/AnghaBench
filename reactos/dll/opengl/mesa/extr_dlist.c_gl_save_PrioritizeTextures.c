#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* PrioritizeTextures ) (TYPE_3__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int /*<<< orphan*/  f; int /*<<< orphan*/  ui; } ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  size_t GLsizei ;
typedef  size_t GLint ;
typedef  TYPE_3__ GLcontext ;
typedef  int /*<<< orphan*/  GLclampf ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_PRIORITIZE_TEXTURE ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void gl_save_PrioritizeTextures( GLcontext *ctx,
                                 GLsizei num, const GLuint *textures,
                                 const GLclampf *priorities )
{
   GLint i;

   for (i=0;i<num;i++) {
      Node *n = alloc_instruction( ctx,  OPCODE_PRIORITIZE_TEXTURE, 2 );
      if (n) {
         n[1].ui = textures[i];
         n[2].f = priorities[i];
      }
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.PrioritizeTextures)( ctx, num, textures, priorities );
   }
}