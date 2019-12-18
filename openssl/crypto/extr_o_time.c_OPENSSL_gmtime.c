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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * gmtime_r (int /*<<< orphan*/  const*,struct tm*) ; 
 scalar_t__ gmtime_s (struct tm*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (struct tm*,struct tm*,int) ; 

struct tm *OPENSSL_gmtime(const time_t *timer, struct tm *result)
{
    struct tm *ts = NULL;

#if defined(OPENSSL_THREADS) && defined(OPENSSL_SYS_VMS)
    {
        /*
         * On VMS, gmtime_r() takes a 32-bit pointer as second argument.
         * Since we can't know that |result| is in a space that can easily
         * translate to a 32-bit pointer, we must store temporarily on stack
         * and copy the result.  The stack is always reachable with 32-bit
         * pointers.
         */
#if defined(OPENSSL_SYS_VMS) && __INITIAL_POINTER_SIZE
# pragma pointer_size save
# pragma pointer_size 32
#endif
        struct tm data, *ts2 = &data;
#if defined OPENSSL_SYS_VMS && __INITIAL_POINTER_SIZE
# pragma pointer_size restore
#endif
        if (gmtime_r(timer, ts2) == NULL)
            return NULL;
        memcpy(result, ts2, sizeof(struct tm));
        ts = result;
    }
#elif defined(OPENSSL_THREADS) && !defined(OPENSSL_SYS_WIN32) && !defined(OPENSSL_SYS_MACOSX)
    if (gmtime_r(timer, result) == NULL)
        return NULL;
    ts = result;
#elif defined (OPENSSL_SYS_WINDOWS) && defined(_MSC_VER) && _MSC_VER >= 1400
    if (gmtime_s(result, timer))
        return NULL;
    ts = result;
#else
    ts = gmtime(timer);
    if (ts == NULL)
        return NULL;

    memcpy(result, ts, sizeof(struct tm));
    ts = result;
#endif
    return ts;
}