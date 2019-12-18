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
struct gl_material {float* ShineTable; int /*<<< orphan*/  Shininess; } ;
struct gl_light {float* VP_inf_norm; float** MatDiffuse; float* h_inf_norm; float** MatSpecular; struct gl_light* NextEnabled; } ;
struct TYPE_6__ {float** BaseColor; struct gl_material* Material; struct gl_light* FirstEnabled; } ;
struct TYPE_7__ {TYPE_2__ Light; TYPE_1__* Visual; } ;
struct TYPE_5__ {float RedScale; float GreenScale; float BlueScale; float AlphaScale; } ;
typedef  size_t GLuint ;
typedef  float GLubyte ;
typedef  size_t GLint ;
typedef  float GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 float A ; 
 float FloatToInt (float) ; 
 float MIN2 (float,float) ; 
 int SHINE_TABLE_SIZE ; 
 float gl_pow (float,int /*<<< orphan*/ ) ; 
 float pow (float,int /*<<< orphan*/ ) ; 

void gl_color_shade_vertices_fast( GLcontext *ctx,
                                   GLuint side,
                                   GLuint n,
                                   /*const*/ GLfloat normal[][3],
                                   GLubyte color[][4] )
{
   GLint j;
   GLfloat rscale, gscale, bscale, ascale;
   GLint sumA;
   GLfloat *baseColor = ctx->Light.BaseColor[side];

   /* Compute scale factor to go from floats in [0,1] to integers or fixed
    * point values:
    */
   rscale = ctx->Visual->RedScale;
   gscale = ctx->Visual->GreenScale;
   bscale = ctx->Visual->BlueScale;
   ascale = ctx->Visual->AlphaScale;

   /* Alpha is easy to compute, same for all vertices */
   sumA = (GLint) (baseColor[3] * ascale);

   /* Loop over vertices */
   for (j=0;j<n;j++) {
      GLfloat sumR, sumG, sumB;
      GLfloat nx, ny, nz;
      struct gl_light *light;

      /* the normal vector */
      if (side==0) {
         nx = normal[j][0];
         ny = normal[j][1];
         nz = normal[j][2];
      }
      else {
         nx = -normal[j][0];
         ny = -normal[j][1];
         nz = -normal[j][2];
      }

#ifdef SPEED_HACK
      if (nz<0.0F) {
         color[j][0] = 0.0F;
         color[j][1] = 0.0F;
         color[j][2] = 0.0F;
         color[j][3] = A;
         continue;
      }
#endif

      /* base color from global illumination and enabled light's ambient */
      sumR = baseColor[0];
      sumG = baseColor[1];
      sumB = baseColor[2];

      /* Add contribution from each light source */
      for (light=ctx->Light.FirstEnabled; light; light=light->NextEnabled) {
         GLfloat n_dot_VP;     /* n dot VP */

         n_dot_VP = nx * light->VP_inf_norm[0]
                  + ny * light->VP_inf_norm[1]
                  + nz * light->VP_inf_norm[2];

         /* diffuse and specular terms */
         if (n_dot_VP>0.0F) {
            GLfloat n_dot_h;
            GLfloat *lightMatDiffuse = light->MatDiffuse[side];

            /** add diffuse term **/
            sumR += n_dot_VP * lightMatDiffuse[0];
            sumG += n_dot_VP * lightMatDiffuse[1];
            sumB += n_dot_VP * lightMatDiffuse[2];

            /** specular term **/
            /* dot product of n and h_inf_norm */
            n_dot_h = nx * light->h_inf_norm[0]
                    + ny * light->h_inf_norm[1]
                    + nz * light->h_inf_norm[2];
            if (n_dot_h>0.0F) {
               if (n_dot_h>1.0F) {
                  /* only happens if Magnitude(n) > 1.0 */
                  GLfloat spec_coef = pow( n_dot_h,
                                        ctx->Light.Material[side].Shininess );
                  if (spec_coef>1.0e-10F) {
                     sumR += spec_coef * light->MatSpecular[side][0];
                     sumG += spec_coef * light->MatSpecular[side][1];
                     sumB += spec_coef * light->MatSpecular[side][2];
                  }
               }
               else {
                  /* use table lookup approximation */
                  int k = (int) (n_dot_h * (GLfloat) (SHINE_TABLE_SIZE-1));
                  struct gl_material *m = &ctx->Light.Material[side];
                  GLfloat spec_coef;
                  if (m->ShineTable[k] < 0.0F)
                     m->ShineTable[k] = gl_pow( n_dot_h, m->Shininess );
                  spec_coef = m->ShineTable[k];
                  sumR += spec_coef * light->MatSpecular[side][0];
                  sumG += spec_coef * light->MatSpecular[side][1];
                  sumB += spec_coef * light->MatSpecular[side][2];
               }
            }
         }

      } /*loop over lights*/

      /* clamp and convert to integer or fixed point */
      color[j][0] = FloatToInt(MIN2( sumR, 1.0F ) * rscale);
      color[j][1] = FloatToInt(MIN2( sumG, 1.0F ) * gscale);
      color[j][2] = FloatToInt(MIN2( sumB, 1.0F ) * bscale);
      color[j][3] = sumA;

   } /*loop over vertices*/
}