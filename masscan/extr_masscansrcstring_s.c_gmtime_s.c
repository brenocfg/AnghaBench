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
typedef  int errno_t ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (struct tm*,struct tm*,int) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 

errno_t gmtime_s(struct tm* _tm, const time_t *time)
{
    struct tm *x;

    x = gmtime(time);
    if (x == NULL) {
        memset(_tm, 0, sizeof(*_tm));
        return -1;
    }
    memcpy(_tm, x, sizeof(*_tm));

    return 0;
}