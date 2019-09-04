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
 int /*<<< orphan*/  LSAPI_Write_Stderr (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void sapi_lsapi_log_message(char *message, int syslog_type_int)
{
    char buf[8192];
    int len = strlen( message );
    if ( *(message + len - 1 ) != '\n' )
    {
        snprintf( buf, 8191, "%s\n", message );
        message = buf;
        if (len > 8191)
            len = 8191;
        ++len;
    }
    LSAPI_Write_Stderr( message, len);
}