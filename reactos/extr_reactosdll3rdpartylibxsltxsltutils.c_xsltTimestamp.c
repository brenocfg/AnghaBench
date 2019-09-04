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

long
xsltTimestamp(void)
{
#ifdef XSLT_WIN32_PERFORMANCE_COUNTER
    BOOL ok;
    LARGE_INTEGER performanceCount;
    LARGE_INTEGER performanceFrequency;
    LONGLONG quadCount;
    double seconds;
    static LONGLONG startupQuadCount = 0;
    static LONGLONG startupQuadFreq = 0;

    ok = QueryPerformanceCounter(&performanceCount);
    if (!ok)
        return 0;
    quadCount = performanceCount.QuadPart;
    if (calibration < 0) {
        calibration = 0;
        ok = QueryPerformanceFrequency(&performanceFrequency);
        if (!ok)
            return 0;
        startupQuadFreq = performanceFrequency.QuadPart;
        startupQuadCount = quadCount;
        return (0);
    }
    if (startupQuadFreq == 0)
        return 0;
    seconds = (quadCount - startupQuadCount) / (double) startupQuadFreq;
    return (long) (seconds * XSLT_TIMESTAMP_TICS_PER_SEC);

#else /* XSLT_WIN32_PERFORMANCE_COUNTER */
#ifdef HAVE_CLOCK_GETTIME
#  if defined(CLOCK_MONOTONIC)
#    define XSLT_CLOCK CLOCK_MONOTONIC
#  elif defined(CLOCK_HIGHRES)
#    define XSLT_CLOCK CLOCK_HIGHRES
#  else
#    define XSLT_CLOCK CLOCK_REALTIME
#  endif
    static struct timespec startup;
    struct timespec cur;
    long tics;

    if (calibration < 0) {
        clock_gettime(XSLT_CLOCK, &startup);
        calibration = 0;
        calibration = xsltCalibrateTimestamps();
        clock_gettime(XSLT_CLOCK, &startup);
        return (0);
    }

    clock_gettime(XSLT_CLOCK, &cur);
    tics = (cur.tv_sec - startup.tv_sec) * XSLT_TIMESTAMP_TICS_PER_SEC;
    tics += (cur.tv_nsec - startup.tv_nsec) /
                          (1000000000l / XSLT_TIMESTAMP_TICS_PER_SEC);

    tics -= calibration;
    return(tics);

#elif HAVE_GETTIMEOFDAY
    static struct timeval startup;
    struct timeval cur;
    long tics;

    if (calibration < 0) {
        gettimeofday(&startup, NULL);
        calibration = 0;
        calibration = xsltCalibrateTimestamps();
        gettimeofday(&startup, NULL);
        return (0);
    }

    gettimeofday(&cur, NULL);
    tics = (cur.tv_sec - startup.tv_sec) * XSLT_TIMESTAMP_TICS_PER_SEC;
    tics += (cur.tv_usec - startup.tv_usec) /
                          (1000000l / XSLT_TIMESTAMP_TICS_PER_SEC);

    tics -= calibration;
    return(tics);
#else

    /* Neither gettimeofday() nor Win32 performance counter available */

    return (0);

#endif /* HAVE_GETTIMEOFDAY */
#endif /* XSLT_WIN32_PERFORMANCE_COUNTER */
}