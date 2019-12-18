#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* Material; } ;
struct TYPE_9__ {TYPE_2__ Light; } ;
struct TYPE_7__ {int /*<<< orphan*/  SpecularIndex; int /*<<< orphan*/  DiffuseIndex; int /*<<< orphan*/  AmbientIndex; int /*<<< orphan*/  Shininess; int /*<<< orphan*/  Emission; int /*<<< orphan*/  Specular; int /*<<< orphan*/  Diffuse; int /*<<< orphan*/  Ambient; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  GL_AMBIENT 133 
 scalar_t__ GL_BACK ; 
#define  GL_COLOR_INDEXES 132 
#define  GL_DIFFUSE 131 
#define  GL_EMISSION 130 
 scalar_t__ GL_FRONT ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_SHININESS 129 
#define  GL_SPECULAR 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetMaterialfv( GLcontext *ctx,
                       GLenum face, GLenum pname, GLfloat *params )
{
   GLuint f;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetMaterialfv" );
      return;
   }
   if (face==GL_FRONT) {
      f = 0;
   }
   else if (face==GL_BACK) {
      f = 1;
   }
   else {
      gl_error( ctx, GL_INVALID_ENUM, "glGetMaterialfv(face)" );
      return;
   }
   switch (pname) {
      case GL_AMBIENT:
         COPY_4V( params, ctx->Light.Material[f].Ambient );
         break;
      case GL_DIFFUSE:
         COPY_4V( params, ctx->Light.Material[f].Diffuse );
	 break;
      case GL_SPECULAR:
         COPY_4V( params, ctx->Light.Material[f].Specular );
	 break;
      case GL_EMISSION:
	 COPY_4V( params, ctx->Light.Material[f].Emission );
	 break;
      case GL_SHININESS:
	 *params = ctx->Light.Material[f].Shininess;
	 break;
      case GL_COLOR_INDEXES:
	 params[0] = ctx->Light.Material[f].AmbientIndex;
	 params[1] = ctx->Light.Material[f].DiffuseIndex;
	 params[2] = ctx->Light.Material[f].SpecularIndex;
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetMaterialfv(pname)" );
   }
}