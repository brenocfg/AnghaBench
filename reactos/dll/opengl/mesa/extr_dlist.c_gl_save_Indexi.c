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
struct TYPE_8__ {int /*<<< orphan*/  (* Indexi ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int /*<<< orphan*/  i; } ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_INDEX ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void gl_save_Indexi( GLcontext *ctx, GLint index )
{
   Node *n = alloc_instruction( ctx, OPCODE_INDEX, 1 );
   if (n) {
      n[1].i = index;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.Indexi)( ctx, index );
   }
}