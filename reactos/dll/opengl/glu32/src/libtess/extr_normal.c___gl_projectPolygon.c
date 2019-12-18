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
struct TYPE_9__ {int* normal; int* sUnit; int* tUnit; TYPE_1__* mesh; } ;
struct TYPE_8__ {int* coords; void* t; void* s; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_2__ vHead; } ;
typedef  int GLdouble ;
typedef  TYPE_2__ GLUvertex ;
typedef  TYPE_3__ GLUtesselator ;

/* Variables and functions */
 int /*<<< orphan*/  CheckOrientation (TYPE_3__*) ; 
 int /*<<< orphan*/  ComputeNormal (TYPE_3__*,int*) ; 
 void* Dot (int*,int*) ; 
 int FALSE ; 
 int LongAxis (int*) ; 
 int /*<<< orphan*/  Normalize (int*) ; 
 int S_UNIT_X ; 
 int S_UNIT_Y ; 
 int TRUE ; 
 int w ; 

void __gl_projectPolygon( GLUtesselator *tess )
{
  GLUvertex *v, *vHead = &tess->mesh->vHead;
  GLdouble norm[3];
  GLdouble *sUnit, *tUnit;
  int i, computedNormal = FALSE;

  norm[0] = tess->normal[0];
  norm[1] = tess->normal[1];
  norm[2] = tess->normal[2];
  if( norm[0] == 0 && norm[1] == 0 && norm[2] == 0 ) {
    ComputeNormal( tess, norm );
    computedNormal = TRUE;
  }
  sUnit = tess->sUnit;
  tUnit = tess->tUnit;
  i = LongAxis( norm );

#if defined(FOR_TRITE_TEST_PROGRAM) || defined(TRUE_PROJECT)
  /* Choose the initial sUnit vector to be approximately perpendicular
   * to the normal.
   */
  Normalize( norm );

  sUnit[i] = 0;
  sUnit[(i+1)%3] = S_UNIT_X;
  sUnit[(i+2)%3] = S_UNIT_Y;

  /* Now make it exactly perpendicular */
  w = Dot( sUnit, norm );
  sUnit[0] -= w * norm[0];
  sUnit[1] -= w * norm[1];
  sUnit[2] -= w * norm[2];
  Normalize( sUnit );

  /* Choose tUnit so that (sUnit,tUnit,norm) form a right-handed frame */
  tUnit[0] = norm[1]*sUnit[2] - norm[2]*sUnit[1];
  tUnit[1] = norm[2]*sUnit[0] - norm[0]*sUnit[2];
  tUnit[2] = norm[0]*sUnit[1] - norm[1]*sUnit[0];
  Normalize( tUnit );
#else
  /* Project perpendicular to a coordinate axis -- better numerically */
  sUnit[i] = 0;
  sUnit[(i+1)%3] = S_UNIT_X;
  sUnit[(i+2)%3] = S_UNIT_Y;

  tUnit[i] = 0;
  tUnit[(i+1)%3] = (norm[i] > 0) ? -S_UNIT_Y : S_UNIT_Y;
  tUnit[(i+2)%3] = (norm[i] > 0) ? S_UNIT_X : -S_UNIT_X;
#endif

  /* Project the vertices onto the sweep plane */
  for( v = vHead->next; v != vHead; v = v->next ) {
    v->s = Dot( v->coords, sUnit );
    v->t = Dot( v->coords, tUnit );
  }
  if( computedNormal ) {
    CheckOrientation( tess );
  }
}