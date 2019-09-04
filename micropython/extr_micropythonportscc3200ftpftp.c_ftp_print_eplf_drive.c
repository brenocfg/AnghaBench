#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int tm_mon; int tm_mday; int tm_year; int tm_hour; int tm_min; } ;
typedef  TYPE_1__ timeutils_struct_time_t ;
struct TYPE_5__ {char* month; } ;

/* Variables and functions */
 scalar_t__ FTP_UNIX_SECONDS_180_DAYS ; 
 scalar_t__ FTP_UNIX_TIME_20000101 ; 
 scalar_t__ FTP_UNIX_TIME_20150101 ; 
 TYPE_3__* ftp_month ; 
 scalar_t__ pyb_rtc_get_seconds () ; 
 int snprintf (char*,scalar_t__,char*,char*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  timeutils_seconds_since_2000_to_struct_time (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static int ftp_print_eplf_drive (char *dest, uint32_t destsize, const char *name) {
    timeutils_struct_time_t tm;
    uint32_t tseconds;
    char *type = "d";

    timeutils_seconds_since_2000_to_struct_time((FTP_UNIX_TIME_20150101 - FTP_UNIX_TIME_20000101), &tm);

    tseconds = pyb_rtc_get_seconds();
    if (FTP_UNIX_SECONDS_180_DAYS < tseconds - (FTP_UNIX_TIME_20150101 - FTP_UNIX_TIME_20000101)) {
        return snprintf(dest, destsize, "%srw-rw-r--   1 root  root %9u %s %2u %5u %s\r\n",
                        type, 0, ftp_month[(tm.tm_mon - 1)].month, tm.tm_mday, tm.tm_year, name);
    }
    else {
        return snprintf(dest, destsize, "%srw-rw-r--   1 root  root %9u %s %2u %02u:%02u %s\r\n",
                        type, 0, ftp_month[(tm.tm_mon - 1)].month, tm.tm_mday, tm.tm_hour, tm.tm_min, name);
    }
}