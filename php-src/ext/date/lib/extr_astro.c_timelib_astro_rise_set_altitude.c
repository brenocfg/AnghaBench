#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int h; int i; int s; scalar_t__ sse; int /*<<< orphan*/  d; int /*<<< orphan*/  m; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ timelib_time ;
typedef  scalar_t__ timelib_sll ;

/* Variables and functions */
 double acosd (double) ; 
 scalar_t__ astro_GMST0 (double) ; 
 double astro_rev180 (double) ; 
 double astro_revolution (scalar_t__) ; 
 int /*<<< orphan*/  astro_sun_RA_dec (double,double*,double*,double*) ; 
 double cosd (double) ; 
 double sind (double) ; 
 TYPE_1__* timelib_time_ctor () ; 
 int /*<<< orphan*/  timelib_time_dtor (TYPE_1__*) ; 
 int timelib_ts_to_j2000 (scalar_t__) ; 
 int /*<<< orphan*/  timelib_update_ts (TYPE_1__*,int /*<<< orphan*/ *) ; 

int timelib_astro_rise_set_altitude(timelib_time *t_loc, double lon, double lat, double altit, int upper_limb, double *h_rise, double *h_set, timelib_sll *ts_rise, timelib_sll *ts_set, timelib_sll *ts_transit)
{
	double  d,  /* Days since 2000 Jan 0.0 (negative before) */
	sr,         /* Solar distance, astronomical units */
	sRA,        /* Sun's Right Ascension */
	sdec,       /* Sun's declination */
	sradius,    /* Sun's apparent radius */
	t,          /* Diurnal arc */
	tsouth,     /* Time when Sun is at south */
	sidtime;    /* Local sidereal time */
	timelib_time *t_utc;
	timelib_sll   timestamp, old_sse;

	int rc = 0; /* Return cde from function - usually 0 */

	/* Normalize time */
	old_sse = t_loc->sse;
	t_loc->h = 12;
	t_loc->i = t_loc->s = 0;
	timelib_update_ts(t_loc, NULL);

	/* Calculate TS belonging to UTC 00:00 of the current day, for input into
	 * the algorithm */
	t_utc = timelib_time_ctor();
	t_utc->y = t_loc->y;
	t_utc->m = t_loc->m;
	t_utc->d = t_loc->d;
	t_utc->h = t_utc->i = t_utc->s = 0;
	timelib_update_ts(t_utc, NULL);

	/* Compute d of 12h local mean solar time */
	timestamp = t_utc->sse;
	d = timelib_ts_to_j2000(timestamp) + 2 - lon/360.0;

	/* Compute local sidereal time of this moment */
	sidtime = astro_revolution(astro_GMST0(d) + 180.0 + lon);

	/* Compute Sun's RA + Decl at this moment */
	astro_sun_RA_dec( d, &sRA, &sdec, &sr );

	/* Compute time when Sun is at south - in hours UT */
	tsouth = 12.0 - astro_rev180(sidtime - sRA) / 15.0;

	/* Compute the Sun's apparent radius, degrees */
	sradius = 0.2666 / sr;

	/* Do correction to upper limb, if necessary */
	if (upper_limb) {
		altit -= sradius;
	}

	/* Compute the diurnal arc that the Sun traverses to reach */
	/* the specified altitude altit: */
	{
		double cost;
		cost = (sind(altit) - sind(lat) * sind(sdec)) / (cosd(lat) * cosd(sdec));
		*ts_transit = t_utc->sse + (tsouth * 3600);
		if (cost >= 1.0) {
			rc = -1;
			t = 0.0;       /* Sun always below altit */

			*ts_rise = *ts_set = t_utc->sse + (tsouth * 3600);
		} else if (cost <= -1.0) {
			rc = +1;
			t = 12.0;      /* Sun always above altit */

			*ts_rise = t_loc->sse - (12 * 3600);
			*ts_set  = t_loc->sse + (12 * 3600);
		} else {
			t = acosd(cost) / 15.0;   /* The diurnal arc, hours */

			/* Store rise and set times - as Unix Timestamp */
			*ts_rise = ((tsouth - t) * 3600) + t_utc->sse;
			*ts_set  = ((tsouth + t) * 3600) + t_utc->sse;

			*h_rise = (tsouth - t);
			*h_set  = (tsouth + t);
		}
	}

	/* Kill temporary time and restore original sse */
	timelib_time_dtor(t_utc);
	t_loc->sse = old_sse;

	return rc;
}