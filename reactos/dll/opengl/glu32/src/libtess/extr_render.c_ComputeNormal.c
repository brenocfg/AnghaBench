#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double* coords; } ;
struct TYPE_4__ {int cacheCount; TYPE_2__* cache; } ;
typedef  double GLdouble ;
typedef  TYPE_1__ GLUtesselator ;
typedef  TYPE_2__ CachedVertex ;

/* Variables and functions */
 int SIGN_INCONSISTENT ; 

__attribute__((used)) static int ComputeNormal( GLUtesselator *tess, GLdouble norm[3], int check )
/*
 * If check==FALSE, we compute the polygon normal and place it in norm[].
 * If check==TRUE, we check that each triangle in the fan from v0 has a
 * consistent orientation with respect to norm[].  If triangles are
 * consistently oriented CCW, return 1; if CW, return -1; if all triangles
 * are degenerate return 0; otherwise (no consistent orientation) return
 * SIGN_INCONSISTENT.
 */
{
  CachedVertex *v0 = tess->cache;
  CachedVertex *vn = v0 + tess->cacheCount;
  CachedVertex *vc;
  GLdouble dot, xc, yc, zc, xp, yp, zp, n[3];
  int sign = 0;

  /* Find the polygon normal.  It is important to get a reasonable
   * normal even when the polygon is self-intersecting (eg. a bowtie).
   * Otherwise, the computed normal could be very tiny, but perpendicular
   * to the true plane of the polygon due to numerical noise.  Then all
   * the triangles would appear to be degenerate and we would incorrectly
   * decompose the polygon as a fan (or simply not render it at all).
   *
   * We use a sum-of-triangles normal algorithm rather than the more
   * efficient sum-of-trapezoids method (used in CheckOrientation()
   * in normal.c).  This lets us explicitly reverse the signed area
   * of some triangles to get a reasonable normal in the self-intersecting
   * case.
   */
  if( ! check ) {
    norm[0] = norm[1] = norm[2] = 0.0;
  }

  vc = v0 + 1;
  xc = vc->coords[0] - v0->coords[0];
  yc = vc->coords[1] - v0->coords[1];
  zc = vc->coords[2] - v0->coords[2];
  while( ++vc < vn ) {
    xp = xc; yp = yc; zp = zc;
    xc = vc->coords[0] - v0->coords[0];
    yc = vc->coords[1] - v0->coords[1];
    zc = vc->coords[2] - v0->coords[2];

    /* Compute (vp - v0) cross (vc - v0) */
    n[0] = yp*zc - zp*yc;
    n[1] = zp*xc - xp*zc;
    n[2] = xp*yc - yp*xc;

    dot = n[0]*norm[0] + n[1]*norm[1] + n[2]*norm[2];
    if( ! check ) {
      /* Reverse the contribution of back-facing triangles to get
       * a reasonable normal for self-intersecting polygons (see above)
       */
      if( dot >= 0 ) {
	norm[0] += n[0]; norm[1] += n[1]; norm[2] += n[2];
      } else {
	norm[0] -= n[0]; norm[1] -= n[1]; norm[2] -= n[2];
      }
    } else if( dot != 0 ) {
      /* Check the new orientation for consistency with previous triangles */
      if( dot > 0 ) {
	if( sign < 0 ) return SIGN_INCONSISTENT;
	sign = 1;
      } else {
	if( sign > 0 ) return SIGN_INCONSISTENT;
	sign = -1;
      }
    }
  }
  return sign;
}