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
 int /*<<< orphan*/  astro_sunpos (double,double*,double*) ; 
 double atan2d (double,double) ; 
 double cosd (double) ; 
 double sind (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static void astro_sun_RA_dec(double d, double *RA, double *dec, double *r)
{
	double lon, obl_ecl, x, y, z;

	/* Compute Sun's ecliptical coordinates */
	astro_sunpos(d, &lon, r);

	/* Compute ecliptic rectangular coordinates (z=0) */
	x = *r * cosd(lon);
	y = *r * sind(lon);

	/* Compute obliquity of ecliptic (inclination of Earth's axis) */
	obl_ecl = 23.4393 - 3.563E-7 * d;

	/* Convert to equatorial rectangular coordinates - x is unchanged */
	z = y * sind(obl_ecl);
	y = y * cosd(obl_ecl);

	/* Convert to spherical coordinates */
	*RA = atan2d(y, x);
	*dec = atan2d(z, sqrt(x*x + y*y));
}