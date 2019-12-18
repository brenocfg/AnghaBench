#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {int /*<<< orphan*/  Findex; int /*<<< orphan*/  Index; int /*<<< orphan*/  Fcolor; int /*<<< orphan*/  Color; scalar_t__ MonoColor; int /*<<< orphan*/  MonoNormal; scalar_t__ Count; scalar_t__ Start; } ;
struct pixel_buffer {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  TwoSide; } ;
struct TYPE_23__ {TYPE_5__ Model; int /*<<< orphan*/  Enabled; } ;
struct TYPE_21__ {int /*<<< orphan*/  Index; int /*<<< orphan*/ * ByteColor; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* Index ) (TYPE_7__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Color ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Begin ) (TYPE_7__*,int) ;} ;
struct TYPE_18__ {scalar_t__ Vertex3f; } ;
struct TYPE_24__ {int Primitive; int LightTwoSide; TYPE_6__ Light; int /*<<< orphan*/  StippleCounter; TYPE_4__ Current; TYPE_3__ Driver; TYPE_2__* Visual; scalar_t__ MonoPixels; TYPE_1__ Exec; scalar_t__ NewState; scalar_t__ NewProjectionMatrix; scalar_t__ NewModelViewMatrix; struct pixel_buffer* PB; struct vertex_buffer* VB; } ;
struct TYPE_19__ {scalar_t__ RGBAflag; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLenum ;
typedef  TYPE_7__ GLcontext ;

/* Variables and functions */
 int GL_BITMAP ; 
 void* GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int const GL_LINE ; 
#define  GL_LINES 137 
#define  GL_LINE_LOOP 136 
#define  GL_LINE_STRIP 135 
 int const GL_POINT ; 
#define  GL_POINTS 134 
#define  GL_POLYGON 133 
#define  GL_QUADS 132 
#define  GL_QUAD_STRIP 131 
#define  GL_TRIANGLES 130 
#define  GL_TRIANGLE_FAN 129 
#define  GL_TRIANGLE_STRIP 128 
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_7__*) ; 
 int /*<<< orphan*/  PB_INIT (struct pixel_buffer*,int const) ; 
 int /*<<< orphan*/  begin_time ; 
 int /*<<< orphan*/  gl_analyze_modelview_matrix (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_analyze_projection_matrix (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_set_vertex_function (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_time () ; 
 int /*<<< orphan*/  gl_update_state (TYPE_7__*) ; 
 scalar_t__ gl_vertex3f_nop ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,int /*<<< orphan*/ ) ; 

void gl_Begin( GLcontext *ctx, GLenum p )
{
   struct vertex_buffer *VB = ctx->VB;
   struct pixel_buffer *PB = ctx->PB;
#ifdef PROFILE
   begin_time = gl_time();
#endif

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glBegin" );
      return;
   }
   if (ctx->NewModelViewMatrix) {
      gl_analyze_modelview_matrix(ctx);
   }
   if (ctx->NewProjectionMatrix) {
      gl_analyze_projection_matrix(ctx);
   }
   if (ctx->NewState) {
      gl_update_state(ctx);
   }
   else if (ctx->Exec.Vertex3f==gl_vertex3f_nop) {
      gl_set_vertex_function(ctx);
   }

   if (ctx->Driver.Begin) {
      (*ctx->Driver.Begin)( ctx, p );
   }

   ctx->Primitive = p;
   VB->Start = VB->Count = 0;

   VB->MonoColor = ctx->MonoPixels;
   VB->MonoNormal = GL_TRUE;
   if (VB->MonoColor) {
      /* All pixels generated are likely to be the same color so have
       * the device driver set the "monocolor" now.
       */
      if (ctx->Visual->RGBAflag) {
         GLubyte r = ctx->Current.ByteColor[0];
         GLubyte g = ctx->Current.ByteColor[1];
         GLubyte b = ctx->Current.ByteColor[2];
         GLubyte a = ctx->Current.ByteColor[3];
         (*ctx->Driver.Color)( ctx, r, g, b, a );
      }
      else {
         (*ctx->Driver.Index)( ctx, ctx->Current.Index );
      }
   }

   /* By default use front color/index.  Two-sided lighting may override. */
   VB->Color = VB->Fcolor;
   VB->Index = VB->Findex;

   switch (ctx->Primitive) {
      case GL_POINTS:
	 ctx->LightTwoSide = GL_FALSE;
	 PB_INIT( PB, GL_POINT );
	 break;
      case GL_LINES:
      case GL_LINE_STRIP:
      case GL_LINE_LOOP:
	 ctx->LightTwoSide = GL_FALSE;
	 ctx->StippleCounter = 0;
	 PB_INIT( PB, GL_LINE );
         break;
      case GL_TRIANGLES:
      case GL_TRIANGLE_STRIP:
      case GL_TRIANGLE_FAN:
      case GL_QUADS:
      case GL_QUAD_STRIP:
      case GL_POLYGON:
	 ctx->LightTwoSide = ctx->Light.Enabled && ctx->Light.Model.TwoSide;
	 PB_INIT( PB, GL_POLYGON );
         break;
      default:
	 gl_error( ctx, GL_INVALID_ENUM, "glBegin" );
	 ctx->Primitive = GL_BITMAP;
   }
}