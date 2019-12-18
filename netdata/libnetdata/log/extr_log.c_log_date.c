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
 struct tm* localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  now_realtime_sec () ; 
 scalar_t__ strftime (char*,size_t,char*,struct tm*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void log_date(char *buffer, size_t len) {
    if(unlikely(!buffer || !len))
        return;

    time_t t;
    struct tm *tmp, tmbuf;

    t = now_realtime_sec();
    tmp = localtime_r(&t, &tmbuf);

    if (tmp == NULL) {
        buffer[0] = '\0';
        return;
    }

    if (unlikely(strftime(buffer, len, "%Y-%m-%d %H:%M:%S", tmp) == 0))
        buffer[0] = '\0';

    buffer[len - 1] = '\0';
}