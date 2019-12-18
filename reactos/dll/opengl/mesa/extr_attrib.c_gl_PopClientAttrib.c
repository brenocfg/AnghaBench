#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gl_pixelstore_attrib {int dummy; } ;
struct gl_attrib_node {int kind; scalar_t__ data; struct gl_attrib_node* next; } ;
struct gl_array_attrib {int dummy; } ;
struct TYPE_6__ {size_t ClientAttribStackDepth; int /*<<< orphan*/  NewState; int /*<<< orphan*/  Array; int /*<<< orphan*/  Unpack; int /*<<< orphan*/  Pack; struct gl_attrib_node** ClientAttribStack; } ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
#define  GL_CLIENT_PACK_BIT 130 
#define  GL_CLIENT_UNPACK_BIT 129 
#define  GL_CLIENT_VERTEX_ARRAY_BIT 128 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_STACK_UNDERFLOW ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_1__*) ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  NEW_ALL ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  gl_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_problem (TYPE_1__*,char*) ; 

void gl_PopClientAttrib( GLcontext *ctx )
{
   struct gl_attrib_node *attr, *next;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPopClientAttrib" );
      return;
   }

   if (ctx->ClientAttribStackDepth==0) {
      gl_error( ctx, GL_STACK_UNDERFLOW, "glPopClientAttrib" );
      return;
   }

   ctx->ClientAttribStackDepth--;
   attr = ctx->ClientAttribStack[ctx->ClientAttribStackDepth];

   while (attr) {
      switch (attr->kind) {
         case GL_CLIENT_PACK_BIT:
            MEMCPY( &ctx->Pack, attr->data,
                    sizeof(struct gl_pixelstore_attrib) );
            break;
         case GL_CLIENT_UNPACK_BIT:
            MEMCPY( &ctx->Unpack, attr->data,
                    sizeof(struct gl_pixelstore_attrib) );
            break;
         case GL_CLIENT_VERTEX_ARRAY_BIT:
            MEMCPY( &ctx->Array, attr->data,
		    sizeof(struct gl_array_attrib) );
            break;
         default:
            gl_problem( ctx, "Bad attrib flag in PopClientAttrib");
            break;
      }

      next = attr->next;
      free( (void *) attr->data );
      free( (void *) attr );
      attr = next;
   }

   ctx->NewState = NEW_ALL;
}