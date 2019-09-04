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
typedef  scalar_t__ uint ;
typedef  int _u32 ;
struct TYPE_5__ {char* month; } ;
struct TYPE_4__ {int fattrib; int fdate; int ftime; char* fname; scalar_t__ fsize; } ;
typedef  TYPE_1__ FILINFO ;

/* Variables and functions */
 int AM_DIR ; 
 scalar_t__ FTP_UNIX_SECONDS_180_DAYS ; 
 TYPE_3__* ftp_month ; 
 scalar_t__ pyb_rtc_get_seconds () ; 
 int snprintf (char*,scalar_t__,char*,char*,int,char*,scalar_t__,int,...) ; 
 scalar_t__ timeutils_seconds_since_2000 (int,int,int,int,int,int) ; 

__attribute__((used)) static int ftp_print_eplf_item (char *dest, uint32_t destsize, FILINFO *fno) {

    char *type = (fno->fattrib & AM_DIR) ? "d" : "-";
    uint32_t tseconds;
    uint mindex = (((fno->fdate >> 5) & 0x0f) > 0) ? (((fno->fdate >> 5) & 0x0f) - 1) : 0;
    uint day = ((fno->fdate & 0x1f) > 0) ? (fno->fdate & 0x1f) : 1;
    uint fseconds = timeutils_seconds_since_2000(1980 + ((fno->fdate >> 9) & 0x7f),
                                                        (fno->fdate >> 5) & 0x0f,
                                                        fno->fdate & 0x1f,
                                                        (fno->ftime >> 11) & 0x1f,
                                                        (fno->ftime >> 5) & 0x3f,
                                                        2 * (fno->ftime & 0x1f));
    tseconds = pyb_rtc_get_seconds();
    if (FTP_UNIX_SECONDS_180_DAYS < tseconds - fseconds) {
        return snprintf(dest, destsize, "%srw-rw-r--   1 root  root %9u %s %2u %5u %s\r\n",
                        type, (_u32)fno->fsize, ftp_month[mindex].month, day,
                        1980 + ((fno->fdate >> 9) & 0x7f), fno->fname);
    }
    else {
        return snprintf(dest, destsize, "%srw-rw-r--   1 root  root %9u %s %2u %02u:%02u %s\r\n",
                        type, (_u32)fno->fsize, ftp_month[mindex].month, day,
                        (fno->ftime >> 11) & 0x1f, (fno->ftime >> 5) & 0x3f, fno->fname);
    }
}