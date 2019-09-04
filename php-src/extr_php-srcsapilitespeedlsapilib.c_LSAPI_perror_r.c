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
typedef  int /*<<< orphan*/  achError ;
typedef  int /*<<< orphan*/  LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_Write_Stderr_r (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  errno ; 
 int getpid () ; 
 int snprintf (char*,int,char*,int,char const*,char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int LSAPI_perror_r( LSAPI_Request * pReq, const char * pErr1, const char *pErr2 )
{
    char achError[4096];
    int n = snprintf(achError, sizeof(achError), "[%d] %s:%s: %s\n", getpid(),
                     pErr1, (pErr2)?pErr2:"", strerror(errno));
    if (n > (int)sizeof(achError))
        n = sizeof(achError);
    if ( pReq )
        LSAPI_Write_Stderr_r( pReq, achError, n );
    else
        write( STDERR_FILENO, achError, n );
    return 0;
}