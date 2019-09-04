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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_perror_r (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int fp_lve_jail (struct passwd*,char*) ; 
 int /*<<< orphan*/  lsapi_log (char*,int /*<<< orphan*/ ,int,char*) ; 
 int stub1 (struct passwd*,char*) ; 

__attribute__((used)) static int lsapi_jailLVE( LSAPI_Request * pReq, uid_t uid, struct passwd * pw )
{
    int ret = 0;
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
    char  error_msg[1024] = "";
    ret = (*fp_lve_jail)( pw, error_msg );
    if ( ret < 0 )
    {
        lsapi_log("LSAPI: LVE jail(%d) ressult: %d, error: %s !\n",
                  uid, ret, error_msg );
        LSAPI_perror_r( pReq, "LSAPI: jail() failure.", NULL );
        return -1;
    }
#endif
    return ret;
}