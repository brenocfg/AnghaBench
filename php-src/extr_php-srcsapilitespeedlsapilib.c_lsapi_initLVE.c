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
 scalar_t__ atol (char const*) ; 
 char* getenv (char*) ; 
 int init_lve_ex () ; 
 int /*<<< orphan*/  lsapi_load_lve_lib () ; 
 scalar_t__ s_enable_lve ; 
 int /*<<< orphan*/  s_uid ; 

__attribute__((used)) static int lsapi_initLVE(void)
{
    const char * pEnv;
    if ( (pEnv = getenv( "LSAPI_LVE_ENABLE" ))!= NULL )
    {
        s_enable_lve = atol( pEnv );
        pEnv = NULL;
    }
    else if ( (pEnv = getenv( "LVE_ENABLE" ))!= NULL )
    {
        s_enable_lve = atol( pEnv );
        pEnv = NULL;
    }
    if ( s_enable_lve && !s_uid )
    {
        lsapi_load_lve_lib();
        if ( s_enable_lve )
        {
            return init_lve_ex();
        }

    }
    return 0;
}