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
struct TYPE_7__ {TYPE_1__* Light; } ;
struct TYPE_8__ {TYPE_2__ Light; } ;
struct TYPE_6__ {scalar_t__* Position; scalar_t__* Direction; scalar_t__ SpotExponent; scalar_t__ SpotCutoff; scalar_t__ ConstantAttenuation; scalar_t__ LinearAttenuation; scalar_t__ QuadraticAttenuation; int /*<<< orphan*/ * Specular; int /*<<< orphan*/ * Diffuse; int /*<<< orphan*/ * Ambient; } ;
typedef  scalar_t__ GLint ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 scalar_t__ FLOAT_TO_INT (int /*<<< orphan*/ ) ; 
#define  GL_AMBIENT 137 
#define  GL_CONSTANT_ATTENUATION 136 
#define  GL_DIFFUSE 135 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int GL_LIGHT0 ; 
#define  GL_LINEAR_ATTENUATION 134 
#define  GL_POSITION 133 
#define  GL_QUADRATIC_ATTENUATION 132 
#define  GL_SPECULAR 131 
#define  GL_SPOT_CUTOFF 130 
#define  GL_SPOT_DIRECTION 129 
#define  GL_SPOT_EXPONENT 128 
 scalar_t__ MAX_LIGHTS ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetLightiv( GLcontext *ctx, GLenum light, GLenum pname, GLint *params )
{
   GLint l = (GLint) (light - GL_LIGHT0);

   if (l<0 || l>=MAX_LIGHTS) {
      gl_error( ctx, GL_INVALID_ENUM, "glGetLightiv" );
      return;
   }

   switch (pname) {
      case GL_AMBIENT:
         params[0] = FLOAT_TO_INT(ctx->Light.Light[l].Ambient[0]);
         params[1] = FLOAT_TO_INT(ctx->Light.Light[l].Ambient[1]);
         params[2] = FLOAT_TO_INT(ctx->Light.Light[l].Ambient[2]);
         params[3] = FLOAT_TO_INT(ctx->Light.Light[l].Ambient[3]);
         break;
      case GL_DIFFUSE:
         params[0] = FLOAT_TO_INT(ctx->Light.Light[l].Diffuse[0]);
         params[1] = FLOAT_TO_INT(ctx->Light.Light[l].Diffuse[1]);
         params[2] = FLOAT_TO_INT(ctx->Light.Light[l].Diffuse[2]);
         params[3] = FLOAT_TO_INT(ctx->Light.Light[l].Diffuse[3]);
         break;
      case GL_SPECULAR:
         params[0] = FLOAT_TO_INT(ctx->Light.Light[l].Specular[0]);
         params[1] = FLOAT_TO_INT(ctx->Light.Light[l].Specular[1]);
         params[2] = FLOAT_TO_INT(ctx->Light.Light[l].Specular[2]);
         params[3] = FLOAT_TO_INT(ctx->Light.Light[l].Specular[3]);
         break;
      case GL_POSITION:
         params[0] = ctx->Light.Light[l].Position[0];
         params[1] = ctx->Light.Light[l].Position[1];
         params[2] = ctx->Light.Light[l].Position[2];
         params[3] = ctx->Light.Light[l].Position[3];
         break;
      case GL_SPOT_DIRECTION:
         params[0] = ctx->Light.Light[l].Direction[0];
         params[1] = ctx->Light.Light[l].Direction[1];
         params[2] = ctx->Light.Light[l].Direction[2];
         break;
      case GL_SPOT_EXPONENT:
         params[0] = ctx->Light.Light[l].SpotExponent;
         break;
      case GL_SPOT_CUTOFF:
         params[0] = ctx->Light.Light[l].SpotCutoff;
         break;
      case GL_CONSTANT_ATTENUATION:
         params[0] = ctx->Light.Light[l].ConstantAttenuation;
         break;
      case GL_LINEAR_ATTENUATION:
         params[0] = ctx->Light.Light[l].LinearAttenuation;
         break;
      case GL_QUADRATIC_ATTENUATION:
         params[0] = ctx->Light.Light[l].QuadraticAttenuation;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetLightiv" );
         break;
   }
}