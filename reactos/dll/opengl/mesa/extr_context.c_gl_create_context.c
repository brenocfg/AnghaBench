#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {void* ReadBuffer; } ;
struct TYPE_19__ {void* DrawBuffer; } ;
struct TYPE_22__ {int /*<<< orphan*/  Exec; int /*<<< orphan*/  API; struct TYPE_22__* PB; struct TYPE_22__* VB; TYPE_14__* Shared; TYPE_2__ Pixel; TYPE_1__ Color; int /*<<< orphan*/ * Buffer; TYPE_3__* Visual; void* DriverCtx; } ;
struct TYPE_21__ {scalar_t__ DBflag; } ;
struct TYPE_18__ {int /*<<< orphan*/  RefCount; } ;
typedef  TYPE_3__ GLvisual ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_4__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;

/* Variables and functions */
 void* GL_BACK ; 
 void* GL_FRONT ; 
 int /*<<< orphan*/  alloc_proxy_textures (TYPE_4__*) ; 
 TYPE_14__* alloc_shared_state () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  free_shared_state (TYPE_4__*,TYPE_14__*) ; 
 TYPE_4__* gl_alloc_pb () ; 
 TYPE_4__* gl_alloc_vb () ; 
 int /*<<< orphan*/  gl_init_api_function_pointers (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_init_eval () ; 
 int /*<<< orphan*/  gl_init_lists () ; 
 int /*<<< orphan*/  gl_init_math () ; 
 int /*<<< orphan*/  init_timings (TYPE_4__*) ; 
 int /*<<< orphan*/  initialize_context (TYPE_4__*) ; 

GLcontext *gl_create_context( GLvisual *visual,
                              GLcontext *share_list,
                              void *driver_ctx )
{
   GLcontext *ctx;

   /* do some implementation tests */
   assert( sizeof(GLbyte) == 1 );
   assert( sizeof(GLshort) >= 2 );
   assert( sizeof(GLint) >= 4 );
   assert( sizeof(GLubyte) == 1 );
   assert( sizeof(GLushort) >= 2 );
   assert( sizeof(GLuint) >= 4 );

   /* misc one-time initializations */
   gl_init_math();
   gl_init_lists();
   gl_init_eval();

   ctx = (GLcontext *) calloc( 1, sizeof(GLcontext) );
   if (!ctx) {
      return NULL;
   }

   ctx->DriverCtx = driver_ctx;
   ctx->Visual = visual;
   ctx->Buffer = NULL;

   ctx->VB = gl_alloc_vb();
   if (!ctx->VB) {
      free( ctx );
      return NULL;
   }

   ctx->PB = gl_alloc_pb();
   if (!ctx->PB) {
      free( ctx->VB );
      free( ctx );
      return NULL;
   }

   if (share_list) {
      /* share the group of display lists of another context */
      ctx->Shared = share_list->Shared;
   }
   else {
      /* allocate new group of display lists */
      ctx->Shared = alloc_shared_state();
      if (!ctx->Shared) {
         free(ctx->VB);
         free(ctx->PB);
         free(ctx);
         return NULL;
      }
   }
   ctx->Shared->RefCount++;

   initialize_context( ctx );

   if (visual->DBflag) {
      ctx->Color.DrawBuffer = GL_BACK;
      ctx->Pixel.ReadBuffer = GL_BACK;
   }
   else {
      ctx->Color.DrawBuffer = GL_FRONT;
      ctx->Pixel.ReadBuffer = GL_FRONT;
   }

#ifdef PROFILE
   init_timings( ctx );
#endif

#ifdef GL_VERSION_1_1
   if (!alloc_proxy_textures(ctx)) {
      free_shared_state(ctx, ctx->Shared);
      free(ctx->VB);
      free(ctx->PB);
      free(ctx);
      return NULL;
   }
#endif

   gl_init_api_function_pointers( ctx );
   ctx->API = ctx->Exec;   /* GL_EXECUTE is default */

   return ctx;
}