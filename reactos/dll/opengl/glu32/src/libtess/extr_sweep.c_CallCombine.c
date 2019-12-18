#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fatalError; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * coords; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  GLdouble ;
typedef  TYPE_1__ GLUvertex ;
typedef  TYPE_2__ GLUtesselator ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_COMBINE_OR_COMBINE_DATA (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CALL_ERROR_OR_ERROR_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLU_TESS_NEED_COMBINE_CALLBACK ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static void CallCombine( GLUtesselator *tess, GLUvertex *isect,
			 void *data[4], GLfloat weights[4], int needed )
{
  GLdouble coords[3];

  /* Copy coord data in case the callback changes it. */
  coords[0] = isect->coords[0];
  coords[1] = isect->coords[1];
  coords[2] = isect->coords[2];

  isect->data = NULL;
  CALL_COMBINE_OR_COMBINE_DATA( coords, data, weights, &isect->data );
  if( isect->data == NULL ) {
    if( ! needed ) {
      isect->data = data[0];
    } else if( ! tess->fatalError ) {
      /* The only way fatal error is when two edges are found to intersect,
       * but the user has not provided the callback necessary to handle
       * generated intersection points.
       */
      CALL_ERROR_OR_ERROR_DATA( GLU_TESS_NEED_COMBINE_CALLBACK );
      tess->fatalError = TRUE;
    }
  }
}