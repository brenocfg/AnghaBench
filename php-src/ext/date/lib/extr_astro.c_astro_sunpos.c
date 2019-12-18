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

/* Variables and functions */
 double RADEG ; 
 double astro_revolution (double) ; 
 double atan2d (double,double) ; 
 double cosd (double) ; 
 double sind (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static void astro_sunpos(double d, double *lon, double *r)
{
	double M,         /* Mean anomaly of the Sun */
	       w,         /* Mean longitude of perihelion */
	                  /* Note: Sun's mean longitude = M + w */
	       e,         /* Eccentricity of Earth's orbit */
	       E,         /* Eccentric anomaly */
	       x, y,      /* x, y coordinates in orbit */
	       v;         /* True anomaly */

	/* Compute mean elements */
	M = astro_revolution(356.0470 + 0.9856002585 * d);
	w = 282.9404 + 4.70935E-5 * d;
	e = 0.016709 - 1.151E-9 * d;

	/* Compute true longitude and radius vector */
	E = M + e * RADEG * sind(M) * (1.0 + e * cosd(M));
	x = cosd(E) - e;
	y = sqrt(1.0 - e*e) * sind(E);
	*r = sqrt(x*x + y*y);              /* Solar distance */
	v = atan2d(y, x);                  /* True anomaly */
	*lon = v + w;                        /* True solar longitude */
	if (*lon >= 360.0) {
		*lon -= 360.0;                   /* Make it 0..360 degrees */
	}
}