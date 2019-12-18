#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int windingRule; } ;
typedef  int GLboolean ;
typedef  TYPE_1__ GLUtesselator ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  GLU_TESS_WINDING_ABS_GEQ_TWO 132 
#define  GLU_TESS_WINDING_NEGATIVE 131 
#define  GLU_TESS_WINDING_NONZERO 130 
#define  GLU_TESS_WINDING_ODD 129 
#define  GLU_TESS_WINDING_POSITIVE 128 
 int GL_FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLboolean IsWindingInside( GLUtesselator *tess, int n )
{
  switch( tess->windingRule ) {
  case GLU_TESS_WINDING_ODD:
    return (n & 1);
  case GLU_TESS_WINDING_NONZERO:
    return (n != 0);
  case GLU_TESS_WINDING_POSITIVE:
    return (n > 0);
  case GLU_TESS_WINDING_NEGATIVE:
    return (n < 0);
  case GLU_TESS_WINDING_ABS_GEQ_TWO:
    return (n >= 2) || (n <= -2);
  }
  /*LINTED*/
  assert( FALSE );
  /*NOTREACHED*/
  return GL_FALSE;  /* avoid compiler complaints */
}