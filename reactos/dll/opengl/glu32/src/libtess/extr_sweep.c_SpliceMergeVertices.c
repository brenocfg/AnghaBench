#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* data; } ;
struct TYPE_11__ {TYPE_9__* Org; } ;
struct TYPE_10__ {int /*<<< orphan*/  env; } ;
typedef  double GLfloat ;
typedef  TYPE_1__ GLUtesselator ;
typedef  TYPE_2__ GLUhalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  CallCombine (TYPE_1__*,TYPE_9__*,void**,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  __gl_meshSplice (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SpliceMergeVertices( GLUtesselator *tess, GLUhalfEdge *e1,
				 GLUhalfEdge *e2 )
/*
 * Two vertices with idential coordinates are combined into one.
 * e1->Org is kept, while e2->Org is discarded.
 */
{
  void *data[4] = { NULL, NULL, NULL, NULL };
  GLfloat weights[4] = { 0.5, 0.5, 0.0, 0.0 };

  data[0] = e1->Org->data;
  data[1] = e2->Org->data;
  CallCombine( tess, e1->Org, data, weights, FALSE );
  if ( !__gl_meshSplice( e1, e2 ) ) longjmp(tess->env,1);
}