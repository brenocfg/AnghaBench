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
struct TYPE_8__ {int /*<<< orphan*/  (* EdgeFlag ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_2__ Node ;
typedef  TYPE_3__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_EDGE_FLAG ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void gl_save_EdgeFlag( GLcontext *ctx, GLboolean flag )
{
   Node *n = alloc_instruction( ctx, OPCODE_EDGE_FLAG, 1 );
   if (n) {
      n[1].b = flag;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.EdgeFlag)( ctx, flag );
   }
}