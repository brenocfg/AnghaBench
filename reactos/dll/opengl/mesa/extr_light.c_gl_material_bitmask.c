#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int GLuint ;
typedef  int GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BACK_AMBIENT_BIT ; 
 int BACK_DIFFUSE_BIT ; 
 int BACK_EMISSION_BIT ; 
 int BACK_INDEXES_BIT ; 
 int BACK_MATERIAL_BITS ; 
 int BACK_SHININESS_BIT ; 
 int BACK_SPECULAR_BIT ; 
 int FRONT_AMBIENT_BIT ; 
 int FRONT_DIFFUSE_BIT ; 
 int FRONT_EMISSION_BIT ; 
 int FRONT_INDEXES_BIT ; 
 int FRONT_MATERIAL_BITS ; 
 int FRONT_SHININESS_BIT ; 
 int FRONT_SPECULAR_BIT ; 
#define  GL_AMBIENT 134 
#define  GL_AMBIENT_AND_DIFFUSE 133 
 int GL_BACK ; 
#define  GL_COLOR_INDEXES 132 
#define  GL_DIFFUSE 131 
#define  GL_EMISSION 130 
 int GL_FRONT ; 
 int GL_FRONT_AND_BACK ; 
#define  GL_SHININESS 129 
#define  GL_SPECULAR 128 
 int /*<<< orphan*/  gl_problem (int /*<<< orphan*/ *,char*) ; 

GLuint gl_material_bitmask( GLenum face, GLenum pname )
{
   GLuint bitmask = 0;

   /* Make a bitmask indicating what material attribute(s) we're updating */
   switch (pname) {
      case GL_EMISSION:
         bitmask |= FRONT_EMISSION_BIT | BACK_EMISSION_BIT;
         break;
      case GL_AMBIENT:
         bitmask |= FRONT_AMBIENT_BIT | BACK_AMBIENT_BIT;
         break;
      case GL_DIFFUSE:
         bitmask |= FRONT_DIFFUSE_BIT | BACK_DIFFUSE_BIT;
         break;
      case GL_SPECULAR:
         bitmask |= FRONT_SPECULAR_BIT | BACK_SPECULAR_BIT;
         break;
      case GL_SHININESS:
         bitmask |= FRONT_SHININESS_BIT | BACK_SHININESS_BIT;
         break;
      case GL_AMBIENT_AND_DIFFUSE:
         bitmask |= FRONT_AMBIENT_BIT | BACK_AMBIENT_BIT;
         bitmask |= FRONT_DIFFUSE_BIT | BACK_DIFFUSE_BIT;
         break;
      case GL_COLOR_INDEXES:
         bitmask |= FRONT_INDEXES_BIT  | BACK_INDEXES_BIT;
         break;
      default:
         gl_problem(NULL, "Bad param in gl_material_bitmask");
         return 0;
   }

   ASSERT( face==GL_FRONT || face==GL_BACK || face==GL_FRONT_AND_BACK );

   if (face==GL_FRONT) {
      bitmask &= FRONT_MATERIAL_BITS;
   }
   else if (face==GL_BACK) {
      bitmask &= BACK_MATERIAL_BITS;
   }

   return bitmask;
}