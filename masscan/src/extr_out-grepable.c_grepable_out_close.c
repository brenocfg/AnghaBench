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
typedef  int /*<<< orphan*/  timestamp ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct Output {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (struct Output*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  gmtime_s (struct tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
grepable_out_close(struct Output *out, FILE *fp)
{
    time_t now = time(0);
    char timestamp[64];
    struct tm tm;

    UNUSEDPARM(out);

    gmtime_s(&tm, &now);

    //Tue Jan 21 20:23:22 2014
    //%a %b %d %H:%M:%S %Y
    strftime(timestamp, sizeof(timestamp), "%c", &tm);

    fprintf(fp, "# Masscan done at %s\n", 
                timestamp);
}