#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {scalar_t__ Count; scalar_t__ VertexSizeMask; scalar_t__ Start; scalar_t__ Obj; scalar_t__ Eye; scalar_t__ Normal; } ;
struct TYPE_7__ {int /*<<< orphan*/  Normalize; } ;
struct TYPE_8__ {int /*<<< orphan*/  VertexTime; TYPE_1__ Transform; int /*<<< orphan*/  ModelViewInv; scalar_t__ NeedNormals; struct vertex_buffer* VB; } ;
typedef  scalar_t__ GLdouble ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ VERTEX4_BIT ; 
 scalar_t__ gl_time () ; 
 int /*<<< orphan*/  gl_transform_vb_part2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_xform_normals_3fv (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_points3 (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  transform_points4 (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 

void gl_transform_vb_part1( GLcontext *ctx, GLboolean allDone )
{
   struct vertex_buffer *VB = ctx->VB;
#ifdef PROFILE
   GLdouble t0 = gl_time();
#endif

   ASSERT( VB->Count>0 );

   /* Apply the modelview matrix to transform vertexes from Object
    * to Eye coords.
    */
   if (VB->VertexSizeMask==VERTEX4_BIT) {
      transform_points4( ctx, VB->Count - VB->Start,
                         VB->Obj + VB->Start, VB->Eye + VB->Start );
   }
   else {
      transform_points3( ctx, VB->Count - VB->Start,
                         VB->Obj + VB->Start, VB->Eye + VB->Start );
   }

   /* Now transform the normal vectors */
   if (ctx->NeedNormals) {
      gl_xform_normals_3fv( VB->Count - VB->Start,
                            VB->Normal + VB->Start, ctx->ModelViewInv,
                            VB->Normal + VB->Start, ctx->Transform.Normalize );
   }

#ifdef PROFILE
   ctx->VertexTime += gl_time() - t0;
#endif

   /* lighting, project, etc */
   gl_transform_vb_part2( ctx, allDone );
}