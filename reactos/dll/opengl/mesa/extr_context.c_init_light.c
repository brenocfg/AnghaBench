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
struct gl_light {double SpotExponent; double SpotCutoff; double CosCutoff; double ConstantAttenuation; double LinearAttenuation; double QuadraticAttenuation; int /*<<< orphan*/  Enabled; int /*<<< orphan*/  Direction; int /*<<< orphan*/  Position; int /*<<< orphan*/  Specular; int /*<<< orphan*/  Diffuse; int /*<<< orphan*/  Ambient; } ;
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_3V (int /*<<< orphan*/ ,double,double,double) ; 
 int /*<<< orphan*/  ASSIGN_4V (int /*<<< orphan*/ ,double,double,double,double) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  gl_compute_spot_exp_table (struct gl_light*) ; 

__attribute__((used)) static void init_light( struct gl_light *l, GLuint n )
{
   ASSIGN_4V( l->Ambient, 0.0, 0.0, 0.0, 1.0 );
   if (n==0) {
      ASSIGN_4V( l->Diffuse, 1.0, 1.0, 1.0, 1.0 );
      ASSIGN_4V( l->Specular, 1.0, 1.0, 1.0, 1.0 );
   }
   else {
      ASSIGN_4V( l->Diffuse, 0.0, 0.0, 0.0, 1.0 );
      ASSIGN_4V( l->Specular, 0.0, 0.0, 0.0, 1.0 );
   }
   ASSIGN_4V( l->Position, 0.0, 0.0, 1.0, 0.0 );
   ASSIGN_3V( l->Direction, 0.0, 0.0, -1.0 );
   l->SpotExponent = 0.0;
   gl_compute_spot_exp_table( l );
   l->SpotCutoff = 180.0;
   l->CosCutoff = -1.0;
   l->ConstantAttenuation = 1.0;
   l->LinearAttenuation = 0.0;
   l->QuadraticAttenuation = 0.0;
   l->Enabled = GL_FALSE;
}