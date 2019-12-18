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
struct TYPE_6__ {int /*<<< orphan*/  ColorMaterialBitmask; scalar_t__ ColorMaterialEnabled; } ;
struct TYPE_7__ {TYPE_1__ Light; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_AMBIENT 134 
#define  GL_AMBIENT_AND_DIFFUSE 133 
 scalar_t__ GL_BACK ; 
#define  GL_COLOR_INDEXES 132 
#define  GL_DIFFUSE 131 
#define  GL_EMISSION 130 
 scalar_t__ GL_FRONT ; 
 scalar_t__ GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_SHININESS 129 
#define  GL_SPECULAR 128 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_material_bitmask (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gl_set_material (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void gl_Materialfv( GLcontext *ctx,
                    GLenum face, GLenum pname, const GLfloat *params )
{
   GLuint bitmask;

   /* error checking */
   if (face!=GL_FRONT && face!=GL_BACK && face!=GL_FRONT_AND_BACK) {
      gl_error( ctx, GL_INVALID_ENUM, "glMaterial(face)" );
      return;
   }
   switch (pname) {
      case GL_EMISSION:
      case GL_AMBIENT:
      case GL_DIFFUSE:
      case GL_SPECULAR:
      case GL_SHININESS:
      case GL_AMBIENT_AND_DIFFUSE:
      case GL_COLOR_INDEXES:
         /* OK */
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glMaterial(pname)" );
         return;
   }

   /* convert face and pname to a bitmask */
   bitmask = gl_material_bitmask( face, pname );

   if (ctx->Light.ColorMaterialEnabled) {
      /* The material values specified by glColorMaterial() can't be */
      /* updated by glMaterial() while GL_COLOR_MATERIAL is enabled! */
      bitmask &= ~ctx->Light.ColorMaterialBitmask;
   }

   gl_set_material( ctx, bitmask, params );
}