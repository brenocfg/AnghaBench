#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Save; int /*<<< orphan*/  Exec; } ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  check_pointers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dlist_pointers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_exec_pointers (int /*<<< orphan*/ *) ; 

void gl_init_api_function_pointers( GLcontext *ctx )
{
   init_exec_pointers( &ctx->Exec );

   init_dlist_pointers( &ctx->Save );

   /* make sure there's no NULL pointers */
   check_pointers( &ctx->Exec );
   check_pointers( &ctx->Save );
}