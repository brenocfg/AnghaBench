#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ PolygonSmooth; scalar_t__ PointSmooth; scalar_t__ PerspectiveCorrection; scalar_t__ LineSmooth; scalar_t__ Fog; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Hint; } ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_DONT_CARE ; 
 scalar_t__ GL_FASTEST ; 
#define  GL_FOG_HINT 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LINE_SMOOTH_HINT 131 
 scalar_t__ GL_NICEST ; 
#define  GL_PERSPECTIVE_CORRECTION_HINT 130 
#define  GL_POINT_SMOOTH_HINT 129 
#define  GL_POLYGON_SMOOTH_HINT 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_ALL ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_Hint( GLcontext *ctx, GLenum target, GLenum mode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glHint" );
      return;
   }
   if (mode!=GL_DONT_CARE && mode!=GL_FASTEST && mode!=GL_NICEST) {
      gl_error( ctx, GL_INVALID_ENUM, "glHint(mode)" );
      return;
   }
   switch (target) {
      case GL_FOG_HINT:
         ctx->Hint.Fog = mode;
         break;
      case GL_LINE_SMOOTH_HINT:
         ctx->Hint.LineSmooth = mode;
         break;
      case GL_PERSPECTIVE_CORRECTION_HINT:
         ctx->Hint.PerspectiveCorrection = mode;
         break;
      case GL_POINT_SMOOTH_HINT:
         ctx->Hint.PointSmooth = mode;
         break;
      case GL_POLYGON_SMOOTH_HINT:
         ctx->Hint.PolygonSmooth = mode;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glHint(target)" );
   }
   ctx->NewState |= NEW_ALL;   /* just to be safe */
}