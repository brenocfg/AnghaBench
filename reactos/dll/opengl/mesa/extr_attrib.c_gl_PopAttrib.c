#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct gl_viewport_attrib {int dummy; } ;
struct gl_transform_attrib {int dummy; } ;
struct gl_texture_attrib {int dummy; } ;
struct gl_stencil_attrib {int dummy; } ;
struct gl_scissor_attrib {int dummy; } ;
struct gl_polygon_attrib {int dummy; } ;
struct gl_point_attrib {int dummy; } ;
struct gl_pixel_attrib {int dummy; } ;
struct gl_list_attrib {int dummy; } ;
struct gl_line_attrib {int dummy; } ;
struct gl_light_attrib {int dummy; } ;
struct gl_hint_attrib {int dummy; } ;
struct gl_fog_attrib {int dummy; } ;
struct gl_eval_attrib {int dummy; } ;
struct gl_enable_attrib {int /*<<< orphan*/  TexGen; int /*<<< orphan*/  Texture; int /*<<< orphan*/  Stencil; int /*<<< orphan*/  Scissor; int /*<<< orphan*/  PolygonStipple; int /*<<< orphan*/  PolygonSmooth; int /*<<< orphan*/  PolygonOffsetFill; int /*<<< orphan*/  PolygonOffsetLine; int /*<<< orphan*/  PolygonOffsetPoint; int /*<<< orphan*/  PointSmooth; int /*<<< orphan*/  Normalize; int /*<<< orphan*/  Map2Vertex4; int /*<<< orphan*/  Map2Vertex3; int /*<<< orphan*/  Map2TextureCoord4; int /*<<< orphan*/  Map2TextureCoord3; int /*<<< orphan*/  Map2TextureCoord2; int /*<<< orphan*/  Map2TextureCoord1; int /*<<< orphan*/  Map2Normal; int /*<<< orphan*/  Map2Index; int /*<<< orphan*/  Map2Color4; int /*<<< orphan*/  Map1Vertex4; int /*<<< orphan*/  Map1Vertex3; int /*<<< orphan*/  Map1TextureCoord4; int /*<<< orphan*/  Map1TextureCoord3; int /*<<< orphan*/  Map1TextureCoord2; int /*<<< orphan*/  Map1TextureCoord1; int /*<<< orphan*/  Map1Normal; int /*<<< orphan*/  Map1Index; int /*<<< orphan*/  Map1Color4; int /*<<< orphan*/  ColorLogicOp; int /*<<< orphan*/  IndexLogicOp; int /*<<< orphan*/  LineStipple; int /*<<< orphan*/  LineSmooth; int /*<<< orphan*/  Lighting; int /*<<< orphan*/  Fog; int /*<<< orphan*/  Dither; int /*<<< orphan*/  DepthTest; int /*<<< orphan*/  CullFace; int /*<<< orphan*/  ColorMaterial; int /*<<< orphan*/ * ClipPlane; int /*<<< orphan*/  Blend; int /*<<< orphan*/  AutoNormal; int /*<<< orphan*/  AlphaTest; } ;
struct gl_depthbuffer_attrib {int dummy; } ;
struct gl_current_attrib {int dummy; } ;
struct gl_colorbuffer_attrib {int dummy; } ;
struct gl_attrib_node {int kind; scalar_t__ data; struct gl_attrib_node* next; } ;
struct gl_accum_attrib {int dummy; } ;
struct TYPE_9__ {size_t DrawBuffer; int OffsetAny; int /*<<< orphan*/  TexGenEnabled; int /*<<< orphan*/  Enabled; int /*<<< orphan*/  StippleFlag; int /*<<< orphan*/  SmoothFlag; int /*<<< orphan*/  OffsetFill; int /*<<< orphan*/  OffsetLine; int /*<<< orphan*/  OffsetPoint; int /*<<< orphan*/  Normalize; int /*<<< orphan*/  Map2Vertex4; int /*<<< orphan*/  Map2Vertex3; int /*<<< orphan*/  Map2TextureCoord4; int /*<<< orphan*/  Map2TextureCoord3; int /*<<< orphan*/  Map2TextureCoord2; int /*<<< orphan*/  Map2TextureCoord1; int /*<<< orphan*/  Map2Normal; int /*<<< orphan*/  Map2Index; int /*<<< orphan*/  Map2Color4; int /*<<< orphan*/  Map1Vertex4; int /*<<< orphan*/  Map1Vertex3; int /*<<< orphan*/  Map1TextureCoord4; int /*<<< orphan*/  Map1TextureCoord3; int /*<<< orphan*/  Map1TextureCoord2; int /*<<< orphan*/  Map1TextureCoord1; int /*<<< orphan*/  Map1Normal; int /*<<< orphan*/  Map1Index; int /*<<< orphan*/  Map1Color4; int /*<<< orphan*/  ColorLogicOpEnabled; int /*<<< orphan*/  IndexLogicOpEnabled; int /*<<< orphan*/  DitherFlag; int /*<<< orphan*/  Test; int /*<<< orphan*/  CullFlag; int /*<<< orphan*/  ColorMaterialEnabled; int /*<<< orphan*/ * ClipEnabled; int /*<<< orphan*/  BlendEnabled; int /*<<< orphan*/  AlphaEnabled; } ;
struct TYPE_8__ {size_t AttribStackDepth; int /*<<< orphan*/  NewState; TYPE_6__ Viewport; TYPE_6__ Texture; TYPE_6__ Transform; TYPE_6__ Stencil; TYPE_6__ Scissor; TYPE_6__* PolygonStipple; TYPE_6__ Polygon; TYPE_6__ Point; TYPE_6__ Pixel; TYPE_6__ List; TYPE_6__ Line; TYPE_6__ Light; TYPE_6__ Hint; TYPE_6__ Fog; TYPE_6__ Eval; TYPE_6__ Color; TYPE_6__ Depth; TYPE_6__ Current; TYPE_6__ Accum; struct gl_attrib_node** AttribStack; } ;
typedef  size_t GLuint ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
#define  GL_ACCUM_BUFFER_BIT 147 
#define  GL_COLOR_BUFFER_BIT 146 
#define  GL_CURRENT_BIT 145 
#define  GL_DEPTH_BUFFER_BIT 144 
#define  GL_ENABLE_BIT 143 
#define  GL_EVAL_BIT 142 
#define  GL_FOG_BIT 141 
#define  GL_HINT_BIT 140 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LIGHTING_BIT 139 
#define  GL_LINE_BIT 138 
#define  GL_LIST_BIT 137 
#define  GL_PIXEL_MODE_BIT 136 
#define  GL_POINT_BIT 135 
#define  GL_POLYGON_BIT 134 
#define  GL_POLYGON_STIPPLE_BIT 133 
#define  GL_SCISSOR_BIT 132 
 int /*<<< orphan*/  GL_STACK_UNDERFLOW ; 
#define  GL_STENCIL_BUFFER_BIT 131 
#define  GL_TEXTURE_BIT 130 
#define  GL_TRANSFORM_BIT 129 
#define  GL_VIEWPORT_BIT 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_1__*) ; 
 size_t MAX_CLIP_PLANES ; 
 int /*<<< orphan*/  MEMCPY (TYPE_6__*,scalar_t__,int) ; 
 int /*<<< orphan*/  NEW_ALL ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  gl_DrawBuffer (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  gl_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_problem (TYPE_1__*,char*) ; 

void gl_PopAttrib( GLcontext* ctx )
{
   struct gl_attrib_node *attr, *next;
   struct gl_enable_attrib *enable;
   GLuint i, oldDrawBuffer;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPopAttrib" );
      return;
   }

   if (ctx->AttribStackDepth==0) {
      gl_error( ctx, GL_STACK_UNDERFLOW, "glPopAttrib" );
      return;
   }

   ctx->AttribStackDepth--;
   attr = ctx->AttribStack[ctx->AttribStackDepth];

   while (attr) {
      switch (attr->kind) {
         case GL_ACCUM_BUFFER_BIT:
            MEMCPY( &ctx->Accum, attr->data, sizeof(struct gl_accum_attrib) );
            break;
         case GL_COLOR_BUFFER_BIT:
	    oldDrawBuffer = ctx->Color.DrawBuffer;
            MEMCPY( &ctx->Color, attr->data,
		    sizeof(struct gl_colorbuffer_attrib) );
	    if (ctx->Color.DrawBuffer != oldDrawBuffer) {
	       gl_DrawBuffer(ctx, ctx->Color.DrawBuffer);
            }
            break;
         case GL_CURRENT_BIT:
            MEMCPY( &ctx->Current, attr->data,
		    sizeof(struct gl_current_attrib) );
            break;
         case GL_DEPTH_BUFFER_BIT:
            MEMCPY( &ctx->Depth, attr->data,
		    sizeof(struct gl_depthbuffer_attrib) );
            break;
         case GL_ENABLE_BIT:
            enable = (struct gl_enable_attrib *) attr->data;
            ctx->Color.AlphaEnabled = enable->AlphaTest;
            ctx->Transform.Normalize = enable->AutoNormal;
            ctx->Color.BlendEnabled = enable->Blend;
	    for (i=0;i<MAX_CLIP_PLANES;i++) {
               ctx->Transform.ClipEnabled[i] = enable->ClipPlane[i];
	    }
	    ctx->Light.ColorMaterialEnabled = enable->ColorMaterial;
	    ctx->Polygon.CullFlag = enable->CullFace;
	    ctx->Depth.Test = enable->DepthTest;
	    ctx->Color.DitherFlag = enable->Dither;
	    ctx->Fog.Enabled = enable->Fog;
	    ctx->Light.Enabled = enable->Lighting;
	    ctx->Line.SmoothFlag = enable->LineSmooth;
	    ctx->Line.StippleFlag = enable->LineStipple;
	    ctx->Color.IndexLogicOpEnabled = enable->IndexLogicOp;
	    ctx->Color.ColorLogicOpEnabled = enable->ColorLogicOp;
	    ctx->Eval.Map1Color4 = enable->Map1Color4;
	    ctx->Eval.Map1Index = enable->Map1Index;
	    ctx->Eval.Map1Normal = enable->Map1Normal;
	    ctx->Eval.Map1TextureCoord1 = enable->Map1TextureCoord1;
	    ctx->Eval.Map1TextureCoord2 = enable->Map1TextureCoord2;
	    ctx->Eval.Map1TextureCoord3 = enable->Map1TextureCoord3;
	    ctx->Eval.Map1TextureCoord4 = enable->Map1TextureCoord4;
	    ctx->Eval.Map1Vertex3 = enable->Map1Vertex3;
	    ctx->Eval.Map1Vertex4 = enable->Map1Vertex4;
	    ctx->Eval.Map2Color4 = enable->Map2Color4;
	    ctx->Eval.Map2Index = enable->Map2Index;
	    ctx->Eval.Map2Normal = enable->Map2Normal;
	    ctx->Eval.Map2TextureCoord1 = enable->Map2TextureCoord1;
	    ctx->Eval.Map2TextureCoord2 = enable->Map2TextureCoord2;
	    ctx->Eval.Map2TextureCoord3 = enable->Map2TextureCoord3;
	    ctx->Eval.Map2TextureCoord4 = enable->Map2TextureCoord4;
	    ctx->Eval.Map2Vertex3 = enable->Map2Vertex3;
	    ctx->Eval.Map2Vertex4 = enable->Map2Vertex4;
	    ctx->Transform.Normalize = enable->Normalize;
	    ctx->Point.SmoothFlag = enable->PointSmooth;
	    ctx->Polygon.OffsetPoint = enable->PolygonOffsetPoint;
	    ctx->Polygon.OffsetLine = enable->PolygonOffsetLine;
	    ctx->Polygon.OffsetFill = enable->PolygonOffsetFill;
            ctx->Polygon.OffsetAny = ctx->Polygon.OffsetPoint ||
                                     ctx->Polygon.OffsetLine ||
                                     ctx->Polygon.OffsetFill;
	    ctx->Polygon.SmoothFlag = enable->PolygonSmooth;
	    ctx->Polygon.StippleFlag = enable->PolygonStipple;
	    ctx->Scissor.Enabled = enable->Scissor;
	    ctx->Stencil.Enabled = enable->Stencil;
	    ctx->Texture.Enabled = enable->Texture;
	    ctx->Texture.TexGenEnabled = enable->TexGen;
            break;
         case GL_EVAL_BIT:
            MEMCPY( &ctx->Eval, attr->data, sizeof(struct gl_eval_attrib) );
            break;
         case GL_FOG_BIT:
            MEMCPY( &ctx->Fog, attr->data, sizeof(struct gl_fog_attrib) );
            break;
         case GL_HINT_BIT:
            MEMCPY( &ctx->Hint, attr->data, sizeof(struct gl_hint_attrib) );
            break;
         case GL_LIGHTING_BIT:
            MEMCPY( &ctx->Light, attr->data, sizeof(struct gl_light_attrib) );
            break;
         case GL_LINE_BIT:
            MEMCPY( &ctx->Line, attr->data, sizeof(struct gl_line_attrib) );
            break;
         case GL_LIST_BIT:
            MEMCPY( &ctx->List, attr->data, sizeof(struct gl_list_attrib) );
            break;
         case GL_PIXEL_MODE_BIT:
            MEMCPY( &ctx->Pixel, attr->data, sizeof(struct gl_pixel_attrib) );
            break;
         case GL_POINT_BIT:
            MEMCPY( &ctx->Point, attr->data, sizeof(struct gl_point_attrib) );
            break;
         case GL_POLYGON_BIT:
            MEMCPY( &ctx->Polygon, attr->data,
		    sizeof(struct gl_polygon_attrib) );
            break;
	 case GL_POLYGON_STIPPLE_BIT:
	    MEMCPY( ctx->PolygonStipple, attr->data, 32*sizeof(GLuint) );
	    break;
         case GL_SCISSOR_BIT:
            MEMCPY( &ctx->Scissor, attr->data,
		    sizeof(struct gl_scissor_attrib) );
            break;
         case GL_STENCIL_BUFFER_BIT:
            MEMCPY( &ctx->Stencil, attr->data,
		    sizeof(struct gl_stencil_attrib) );
            break;
         case GL_TRANSFORM_BIT:
            MEMCPY( &ctx->Transform, attr->data,
		    sizeof(struct gl_transform_attrib) );
            break;
         case GL_TEXTURE_BIT:
            MEMCPY( &ctx->Texture, attr->data,
		    sizeof(struct gl_texture_attrib) );
            break;
         case GL_VIEWPORT_BIT:
            MEMCPY( &ctx->Viewport, attr->data,
		    sizeof(struct gl_viewport_attrib) );
            break;
         default:
            gl_problem( ctx, "Bad attrib flag in PopAttrib");
            break;
      }

      next = attr->next;
      free( (void *) attr->data );
      free( (void *) attr );
      attr = next;
   }

   ctx->NewState = NEW_ALL;
}