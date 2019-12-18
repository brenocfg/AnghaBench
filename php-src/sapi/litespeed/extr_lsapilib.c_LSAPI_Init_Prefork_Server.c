#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int m_iAvoidFork; int m_iMaxChildren; int m_iExtraChildren; int m_iMaxIdleChildren; int m_iChildrenMaxIdleTime; int m_iMaxReqProcessTime; } ;
typedef  TYPE_1__ lsapi_prefork_server ;
typedef  int /*<<< orphan*/ * fn_select_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_PHYS_PAGES ; 
 int /*<<< orphan*/ * g_fnSelect ; 
 TYPE_1__* g_prefork_server ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getppid () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int s_max_busy_workers ; 
 int /*<<< orphan*/  s_pid ; 
 int /*<<< orphan*/  s_ppid ; 
 int /*<<< orphan*/  s_total_pages ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 

int LSAPI_Init_Prefork_Server( int max_children, fn_select_t fp, int avoidFork )
{
    if ( g_prefork_server )
        return 0;
    if ( max_children <= 1 )
        return -1;
    if ( max_children >= 10000)
        max_children = 10000;

    if (s_max_busy_workers == 0)
        s_max_busy_workers = max_children / 2 + 1;

    g_prefork_server = (lsapi_prefork_server *)malloc( sizeof( lsapi_prefork_server ) );
    if ( !g_prefork_server )
        return -1;
    memset( g_prefork_server, 0, sizeof( lsapi_prefork_server ) );

    if ( fp != NULL )
        g_fnSelect = fp;

    s_ppid = getppid();
    s_pid = getpid();
    setpgid( s_pid, s_pid );
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
    s_total_pages = sysconf(_SC_PHYS_PAGES);
#endif
    g_prefork_server->m_iAvoidFork = avoidFork;
    g_prefork_server->m_iMaxChildren = max_children;

    g_prefork_server->m_iExtraChildren = ( avoidFork ) ? 0 : (max_children / 3) ;
    g_prefork_server->m_iMaxIdleChildren = ( avoidFork ) ? (max_children + 1) : (max_children / 3);
    if ( g_prefork_server->m_iMaxIdleChildren == 0 )
        g_prefork_server->m_iMaxIdleChildren = 1;
    g_prefork_server->m_iChildrenMaxIdleTime = 300;
    g_prefork_server->m_iMaxReqProcessTime = 3600;
    return 0;
}