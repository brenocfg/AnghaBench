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
struct TYPE_8__ {int /*<<< orphan*/  (* Color4ubv ) (TYPE_3__*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int /*<<< orphan*/  ub; } ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_COLOR_4UB ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/  const*) ; 

void gl_save_Color4ubv( GLcontext *ctx, const GLubyte *c )
{
   Node *n = alloc_instruction( ctx, OPCODE_COLOR_4UB, 4 );
   if (n) {
      n[1].ub = c[0];
      n[2].ub = c[1];
      n[3].ub = c[2];
      n[4].ub = c[3];
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.Color4ubv)( ctx, c );
   }
}