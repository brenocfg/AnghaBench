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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  NPY_TIME_T ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 scalar_t__ _localtime64_s (struct tm*,int /*<<< orphan*/ *) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ localtime_s (struct tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct tm*,struct tm*,int) ; 

__attribute__((used)) static int
get_localtime(NPY_TIME_T *ts, struct tm *tms)
{
    char *func_name = "<unknown>";
#if defined(_WIN32)
 #if defined(_MSC_VER) && (_MSC_VER >= 1400)
    if (localtime_s(tms, ts) != 0) {
        func_name = "localtime_s";
        goto fail;
    }
 #elif defined(NPY_MINGW_USE_CUSTOM_MSVCR)
    if (_localtime64_s(tms, ts) != 0) {
        func_name = "_localtime64_s";
        goto fail;
    }
 #else
    struct tm *tms_tmp;
    tms_tmp = localtime(ts);
    if (tms_tmp == NULL) {
        func_name = "localtime";
        goto fail;
    }
    memcpy(tms, tms_tmp, sizeof(struct tm));
 #endif
#else
    if (localtime_r(ts, tms) == NULL) {
        func_name = "localtime_r";
        goto fail;
    }
#endif

    return 0;

fail:
    PyErr_Format(PyExc_OSError, "Failed to use '%s' to convert "
                                "to a local time", func_name);
    return -1;
}