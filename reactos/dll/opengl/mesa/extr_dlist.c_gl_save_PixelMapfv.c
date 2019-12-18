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
struct TYPE_8__ {int /*<<< orphan*/  (* PixelMapfv ) (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int i; void* data; int /*<<< orphan*/  e; } ;
typedef  TYPE_2__ Node ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCPY (void*,void*,int) ; 
 int /*<<< orphan*/  OPCODE_PIXEL_MAP ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

void gl_save_PixelMapfv( GLcontext *ctx,
                         GLenum map, GLint mapsize, const GLfloat *values )
{
   Node *n = alloc_instruction( ctx, OPCODE_PIXEL_MAP, 3 );
   if (n) {
      n[1].e = map;
      n[2].i = mapsize;
      n[3].data  = (void *) malloc( mapsize * sizeof(GLfloat) );
      MEMCPY( n[3].data, (void *) values, mapsize * sizeof(GLfloat) );
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.PixelMapfv)( ctx, map, mapsize, values );
   }
}