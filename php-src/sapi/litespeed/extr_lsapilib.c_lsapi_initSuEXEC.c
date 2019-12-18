#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct passwd {int pw_uid; int pw_gid; } ;
struct TYPE_2__ {int m_iMaxChildren; int m_iExtraChildren; } ;

/* Variables and functions */
 int atoi (char const*) ; 
 TYPE_1__* g_prefork_server ; 
 char* getenv (char*) ; 
 struct passwd* getpwnam (char*) ; 
 int readSecret (char const*) ; 
 int s_defaultGid ; 
 int s_defaultUid ; 
 scalar_t__ s_uid ; 

__attribute__((used)) static int lsapi_initSuEXEC(void)
{
    int i;
    struct passwd * pw;
    s_defaultUid = 0;
    s_defaultGid = 0;
    if ( s_uid == 0 )
    {
        const char * p = getenv( "LSAPI_DEFAULT_UID" );
        if ( p )
        {
            i = atoi( p );
            if ( i > 0 )
                s_defaultUid = i;
        }
        p = getenv( "LSAPI_DEFAULT_GID" );
        if ( p )
        {
            i = atoi( p );
            if ( i > 0 )
                s_defaultGid = i;
        }
        p = getenv( "LSAPI_SECRET" );
        if (( !p )||( readSecret(p) == -1 ))
                return -1;
        if ( g_prefork_server )
        {
            if ( g_prefork_server->m_iMaxChildren < 100 )
                g_prefork_server->m_iMaxChildren = 100;
            if ( g_prefork_server->m_iExtraChildren < 1000 )
                g_prefork_server->m_iExtraChildren = 1000;
        }
    }
    if ( !s_defaultUid || !s_defaultGid )
    {
        pw = getpwnam( "nobody" );
        if ( pw )
        {
            if ( !s_defaultUid )
                s_defaultUid = pw->pw_uid;
            if ( !s_defaultGid )
                s_defaultGid = pw->pw_gid;
        }
        else
        {
            if ( !s_defaultUid )
                s_defaultUid = 10000;
            if ( !s_defaultGid )
                s_defaultGid = 10000;
        }
    }
    return 0;
}