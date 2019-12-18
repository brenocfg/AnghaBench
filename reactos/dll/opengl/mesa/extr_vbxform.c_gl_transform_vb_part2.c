#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {scalar_t__ Count; scalar_t__ Start; scalar_t__ Eye; scalar_t__ Clip; scalar_t__ Obj; scalar_t__ Normal; scalar_t__ TexCoord; int /*<<< orphan*/ * Win; int /*<<< orphan*/ * ClipMask; void* ClipOrMask; scalar_t__ ClipAndMask; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* RenderVB ) (TYPE_7__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* RasterSetup ) (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_25__ {scalar_t__ TexGenEnabled; scalar_t__ Enabled; } ;
struct TYPE_24__ {scalar_t__ Fog; } ;
struct TYPE_23__ {scalar_t__ Enabled; } ;
struct TYPE_22__ {scalar_t__ Enabled; } ;
struct TYPE_21__ {scalar_t__ AnyClip; } ;
struct TYPE_27__ {scalar_t__ RenderMode; scalar_t__ TextureMatrixType; TYPE_6__ Driver; int /*<<< orphan*/  VertexCount; int /*<<< orphan*/  VertexTime; scalar_t__ NewTextureMatrix; TYPE_5__ Texture; TYPE_4__ Hint; TYPE_3__ Fog; TYPE_2__ Light; TYPE_1__ Transform; struct vertex_buffer* VB; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLdouble ;
typedef  TYPE_7__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ CLIP_ALL ; 
 void* CLIP_ALL_BITS ; 
 scalar_t__ CLIP_SOME ; 
 void* CLIP_USER_BIT ; 
 scalar_t__ GL_FEEDBACK ; 
 scalar_t__ GL_NICEST ; 
 scalar_t__ MATRIX_IDENTITY ; 
 int /*<<< orphan*/  fog_vertices (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_analyze_texture_matrix (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_render_vb (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_reset_vb (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_texgen (TYPE_7__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ gl_time () ; 
 int /*<<< orphan*/  project_and_cliptest (TYPE_7__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,void**,scalar_t__*) ; 
 int /*<<< orphan*/  shade_vertices (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_texcoords (TYPE_7__*,scalar_t__,scalar_t__) ; 
 scalar_t__ userclip_vertices (TYPE_7__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  viewport_map_vertices (TYPE_7__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void gl_transform_vb_part2( GLcontext *ctx, GLboolean allDone )
{
   struct vertex_buffer *VB = ctx->VB;
#ifdef PROFILE
   GLdouble t0 = gl_time();
#endif

   ASSERT( VB->Count>0 );

   /* Test vertices in eye coordinate space against user clipping planes */
   if (ctx->Transform.AnyClip) {
      GLuint result = userclip_vertices( ctx, VB->Count - VB->Start,
                                         VB->Eye + VB->Start,
                                         VB->ClipMask + VB->Start );
      if (result==CLIP_ALL) {
         /* All vertices were outside one of the clip planes! */
         VB->ClipOrMask = CLIP_ALL_BITS; /* force reset of clipping flags */
         gl_reset_vb( ctx, allDone );
         return;
      }
      else if (result==CLIP_SOME) {
         VB->ClipOrMask = CLIP_USER_BIT;
      }
      else {
         VB->ClipAndMask = 0;
      }
   }

   /* Apply the projection matrix to the Eye coordinates, resulting in
    * Clip coordinates.  Also, compute the ClipMask for each vertex.
    */
   project_and_cliptest( ctx, VB->Count - VB->Start, VB->Eye + VB->Start,
                         VB->Clip + VB->Start, VB->ClipMask + VB->Start,
                         &VB->ClipOrMask, &VB->ClipAndMask );

   if (VB->ClipAndMask) {
      /* All vertices clipped by one plane, all done! */
      /*assert(VB->ClipOrMask);*/
      VB->ClipOrMask = CLIP_ALL_BITS; /* force reset of clipping flags */
      gl_reset_vb( ctx, allDone );
      return;
   }

   /* Lighting */
   if (ctx->Light.Enabled) {
      shade_vertices(ctx);
   }

   /* Per-vertex fog */
   if (ctx->Fog.Enabled && ctx->Hint.Fog!=GL_NICEST) {
      fog_vertices(ctx);
   }

   /* Generate/transform texture coords */
   if (ctx->Texture.Enabled || ctx->RenderMode==GL_FEEDBACK) {
      if (ctx->Texture.TexGenEnabled) {
         gl_texgen( ctx, VB->Count - VB->Start,
                    VB->Obj + VB->Start,
                    VB->Eye + VB->Start,
                    VB->Normal + VB->Start,
                    VB->TexCoord + VB->Start );
      }
      if (ctx->NewTextureMatrix) {
         gl_analyze_texture_matrix(ctx);
      }
      if (ctx->TextureMatrixType!=MATRIX_IDENTITY) {
         transform_texcoords( ctx, VB->Count - VB->Start,
                              VB->TexCoord + VB->Start );
      }
   }

   /* Use the viewport parameters to transform vertices from Clip
    * coordinates to Window coordinates.
    */
   viewport_map_vertices( ctx, VB->Count - VB->Start, VB->Clip + VB->Start,
                          VB->ClipOrMask ? VB->ClipMask + VB->Start : NULL,
                          VB->Win + VB->Start );

   /* Device driver rasterization setup.  3Dfx driver, for example. */
   if (ctx->Driver.RasterSetup) {
      (*ctx->Driver.RasterSetup)( ctx, 0, VB->Count );
   }


#ifdef PROFILE
   ctx->VertexTime += gl_time() - t0;
   ctx->VertexCount += VB->Count - VB->Start;
#endif

   /*
    * Now we're ready to rasterize the Vertex Buffer!!!
    *
    * If the device driver can't rasterize the vertex buffer then we'll
    * do it ourselves.
    */
   if (!ctx->Driver.RenderVB || !(*ctx->Driver.RenderVB)(ctx,allDone)) {
      gl_render_vb( ctx, allDone );
   }
}