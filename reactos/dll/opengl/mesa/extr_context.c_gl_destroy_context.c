#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ RefCount; } ;
struct TYPE_8__ {int /*<<< orphan*/  Proxy2D; int /*<<< orphan*/  Proxy1D; } ;
struct TYPE_9__ {void* PB; void* VB; TYPE_1__ Texture; TYPE_6__* Shared; } ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 TYPE_2__* CC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  free_shared_state (TYPE_2__*,TYPE_6__*) ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  gl_free_texture_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_timings (TYPE_2__*) ; 

void gl_destroy_context( GLcontext *ctx )
{
   if (ctx) {

#ifdef PROFILE
      if (getenv("MESA_PROFILE")) {
         print_timings( ctx );
      }
#endif

      free( ctx->PB );
      free( ctx->VB );

      ctx->Shared->RefCount--;
      assert(ctx->Shared->RefCount>=0);
      if (ctx->Shared->RefCount==0) {
	 /* free shared state */
	 free_shared_state( ctx, ctx->Shared );
      }

      /* Free proxy texture objects */
      gl_free_texture_object( NULL, ctx->Texture.Proxy1D );
      gl_free_texture_object( NULL, ctx->Texture.Proxy2D );

      free( (void *) ctx );

#ifndef THREADS
      if (ctx==CC) {
         CC = NULL;
      }
#endif

   }
}