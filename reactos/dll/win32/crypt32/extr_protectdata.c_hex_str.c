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
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char const* wine_dbg_sprintf (char*,char const*,...) ; 

__attribute__((used)) static const char *
hex_str(const unsigned char *p, int n)
{
    const char * ptr;
    char report[80];
    int r=-1;
    report[0]='\0';
    ptr = wine_dbg_sprintf("%s","");
    while (--n >= 0)
    {
        if (r++ % 20 == 19)
        {
            ptr = wine_dbg_sprintf("%s%s",ptr,report);
            report[0]='\0';
        }
        sprintf(report+strlen(report),"%s%02x", r ? "," : "", *p++);
    }
    return wine_dbg_sprintf("%s%s",ptr,report);
}