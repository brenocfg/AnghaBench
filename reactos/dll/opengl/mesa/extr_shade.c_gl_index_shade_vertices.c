#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gl_material {float* ShineTable; float SpecularIndex; float DiffuseIndex; float AmbientIndex; int /*<<< orphan*/  Shininess; } ;
struct gl_light {double* Position; float* VP_inf_norm; float ConstantAttenuation; float LinearAttenuation; float QuadraticAttenuation; float SpotCutoff; float CosCutoff; double** SpotExpTable; float dli; float sli; int /*<<< orphan*/  NormDirection; struct gl_light* NextEnabled; } ;
struct TYPE_5__ {scalar_t__ LocalViewer; } ;
struct TYPE_6__ {TYPE_1__ Model; struct gl_light* FirstEnabled; struct gl_material* Material; } ;
struct TYPE_7__ {TYPE_2__ Light; } ;
typedef  size_t GLuint ;
typedef  size_t GLint ;
typedef  float GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 float DOT3 (float*,int /*<<< orphan*/ ) ; 
 int EXP_TABLE_SIZE ; 
 float GL_SQRT (float) ; 
 int SHINE_TABLE_SIZE ; 
 float gl_pow (float,int /*<<< orphan*/ ) ; 
 float pow (float,int /*<<< orphan*/ ) ; 

void gl_index_shade_vertices( GLcontext *ctx,
                              GLuint side,
                              GLuint n,
                              GLfloat vertex[][4],
                              GLfloat normal[][3],
                              GLuint indexResult[] )
{
   struct gl_material *mat = &ctx->Light.Material[side];
   GLint j;

   /* loop over vertices */
   for (j=0;j<n;j++) {
      GLfloat index;
      GLfloat diffuse, specular;  /* accumulated diffuse and specular */
      GLfloat nx, ny, nz;  /* normal vector */
      struct gl_light *light;

      if (side==0) {
         /* shade frontside */
         nx = normal[j][0];
         ny = normal[j][1];
         nz = normal[j][2];
      }
      else {
         /* shade backside */
         nx = -normal[j][0];
         ny = -normal[j][1];
         nz = -normal[j][2];
      }

      diffuse = specular = 0.0F;

      /* Accumulate diffuse and specular from each light source */
      for (light=ctx->Light.FirstEnabled; light; light=light->NextEnabled) {
         GLfloat attenuation;
         GLfloat lx, ly, lz;  /* unit vector from vertex to light */
         GLfloat l_dot_norm;  /* dot product of l and n */

         /* compute l and attenuation */
         if (light->Position[3]==0.0) {
            /* directional light */
            /* Effectively, l is a vector from the origin to the light. */
            lx = light->VP_inf_norm[0];
            ly = light->VP_inf_norm[1];
            lz = light->VP_inf_norm[2];
            attenuation = 1.0F;
         }
         else {
            /* positional light */
            GLfloat d;     /* distance from vertex to light */
            lx = light->Position[0] - vertex[j][0];
            ly = light->Position[1] - vertex[j][1];
            lz = light->Position[2] - vertex[j][2];
            d = (GLfloat) GL_SQRT( lx*lx + ly*ly + lz*lz );
            if (d>0.001F) {
               GLfloat invd = 1.0F / d;
               lx *= invd;
               ly *= invd;
               lz *= invd;
            }
            attenuation = 1.0F / (light->ConstantAttenuation
                        + d * (light->LinearAttenuation
                        + d * light->QuadraticAttenuation));
         }

         l_dot_norm = lx*nx + ly*ny + lz*nz;

         if (l_dot_norm>0.0F) {
            GLfloat spot_times_atten;

            /* spotlight factor */
            if (light->SpotCutoff==180.0F) {
               /* not a spot light */
               spot_times_atten = attenuation;
            }
            else {
               GLfloat v[3], dot;
               v[0] = -lx;  /* v points from light to vertex */
               v[1] = -ly;
               v[2] = -lz;
               dot = DOT3( v, light->NormDirection );
               if (dot<=0.0F || dot<light->CosCutoff) {
                  /* outside of cone */
                  spot_times_atten = 0.0F;
               }
               else {
                  double x = dot * (EXP_TABLE_SIZE-1);
                  int k = (int) x;
                  GLfloat spot = light->SpotExpTable[k][0]
                               + (x-k)*light->SpotExpTable[k][1];
                  spot_times_atten = spot * attenuation;
               }
            }

            /* accumulate diffuse term */
            diffuse += l_dot_norm * light->dli * spot_times_atten;

            /* accumulate specular term */
            {
               GLfloat h_x, h_y, h_z, n_dot_h, spec_coef;

               /* specular term */
               if (ctx->Light.Model.LocalViewer) {
                  GLfloat vx, vy, vz, vlen;
                  vx = vertex[j][0];
                  vy = vertex[j][1];
                  vz = vertex[j][2];
                  vlen = GL_SQRT( vx*vx + vy*vy + vz*vz );
                  if (vlen>0.0001F) {
                     GLfloat invlen = 1.0F / vlen;
                     vx *= invlen;
                     vy *= invlen;
                     vz *= invlen;
                  }
                  h_x = lx - vx;
                  h_y = ly - vy;
                  h_z = lz - vz;
               }
               else {
                  h_x = lx;
                  h_y = ly;
                  h_z = lz + 1.0F;
               }
               /* attention: s is not normalized, done later if necessary */
               n_dot_h = h_x*nx + h_y*ny + h_z*nz;

               if (n_dot_h <= 0.0F) {
                  spec_coef = 0.0F;
               }
               else {
                  /* now `correct' the dot product */
                  n_dot_h = n_dot_h / GL_SQRT(h_x*h_x + h_y*h_y + h_z*h_z);
                  if (n_dot_h>1.0F) {
                     spec_coef = pow( n_dot_h, mat->Shininess );
                  }
                  else {
                     int k = (int) (n_dot_h * (GLfloat)(SHINE_TABLE_SIZE-1));
                     if (mat->ShineTable[k] < 0.0F)
                        mat->ShineTable[k] = gl_pow( n_dot_h, mat->Shininess );
                     spec_coef = mat->ShineTable[k];
                  }
               }
               specular += spec_coef * light->sli * spot_times_atten;
            }
         }

      } /*loop over lights*/

      /* Now compute final color index */
      if (specular>1.0F) {
         index = mat->SpecularIndex;
      }
      else {
         GLfloat d_a, s_a;
         d_a = mat->DiffuseIndex - mat->AmbientIndex;
         s_a = mat->SpecularIndex - mat->AmbientIndex;

         index = mat->AmbientIndex
               + diffuse * (1.0F-specular) * d_a
               + specular * s_a;
         if (index>mat->SpecularIndex) {
            index = mat->SpecularIndex;
         }
      }
      indexResult[j] = (GLuint) (GLint) index;

   } /*for vertex*/
}