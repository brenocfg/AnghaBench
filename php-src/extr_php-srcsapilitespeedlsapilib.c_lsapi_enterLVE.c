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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_perror_r (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int fp_lve_enter (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsapi_log (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  lsapi_lve_error (int /*<<< orphan*/ *) ; 
 scalar_t__ s_lve ; 
 int stub1 (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lsapi_enterLVE( LSAPI_Request * pReq, uid_t uid )
{
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
    if ( s_lve && uid ) //root user should not do that
    {
        uint32_t cookie;
        int ret = -1;
        ret = (*fp_lve_enter)(s_lve, uid, -1, -1, &cookie);
        if ( ret < 0 )
        {
            lsapi_log("enter LVE (%d) : ressult: %d !\n", uid, ret );
            LSAPI_perror_r(pReq, "LSAPI: lve_enter() failure, reached resource limit.", NULL );
            lsapi_lve_error( pReq );
            return -1;
        }
    }
#endif

    return 0;
}