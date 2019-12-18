#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  TexCoord2f; } ;
struct TYPE_9__ {int /*<<< orphan*/  TexCoord2f; } ;
struct TYPE_11__ {void** TexCoord; } ;
struct TYPE_12__ {TYPE_3__ API; TYPE_2__ Exec; TYPE_1__* VB; TYPE_4__ Current; } ;
struct TYPE_8__ {int TexCoordSize; } ;
typedef  void* GLfloat ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  gl_TexCoord2f4 ; 
 int /*<<< orphan*/  gl_set_vertex_function (TYPE_5__*) ; 

void gl_TexCoord4f( GLcontext *ctx, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
   ctx->Current.TexCoord[0] = s;
   ctx->Current.TexCoord[1] = t;
   ctx->Current.TexCoord[2] = r;
   ctx->Current.TexCoord[3] = q;
   if (ctx->VB->TexCoordSize==2) {
      /* Have to switch to 4-component texture mode now */
      ctx->VB->TexCoordSize = 4;
      gl_set_vertex_function( ctx );
      ctx->Exec.TexCoord2f = ctx->API.TexCoord2f = gl_TexCoord2f4;
   }
}