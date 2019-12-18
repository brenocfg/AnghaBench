#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* TwoSide; void* LocalViewer; int /*<<< orphan*/  Ambient; } ;
struct TYPE_7__ {TYPE_1__ Model; } ;
struct TYPE_8__ {int /*<<< orphan*/  NewState; TYPE_2__ Light; } ;
typedef  double GLfloat ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ ,double const*) ; 
 void* GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_LIGHT_MODEL_AMBIENT 130 
#define  GL_LIGHT_MODEL_LOCAL_VIEWER 129 
#define  GL_LIGHT_MODEL_TWO_SIDE 128 
 void* GL_TRUE ; 
 int /*<<< orphan*/  NEW_LIGHTING ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void gl_LightModelfv( GLcontext *ctx, GLenum pname, const GLfloat *params )
{
   switch (pname) {
      case GL_LIGHT_MODEL_AMBIENT:
         COPY_4V( ctx->Light.Model.Ambient, params );
         break;
      case GL_LIGHT_MODEL_LOCAL_VIEWER:
         if (params[0]==0.0)
            ctx->Light.Model.LocalViewer = GL_FALSE;
         else
            ctx->Light.Model.LocalViewer = GL_TRUE;
         break;
      case GL_LIGHT_MODEL_TWO_SIDE:
         if (params[0]==0.0)
            ctx->Light.Model.TwoSide = GL_FALSE;
         else
            ctx->Light.Model.TwoSide = GL_TRUE;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glLightModel" );
         break;
   }
   ctx->NewState |= NEW_LIGHTING;
}