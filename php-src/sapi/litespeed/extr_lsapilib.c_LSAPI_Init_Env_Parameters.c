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
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  fn_select_t ;
struct TYPE_2__ {int /*<<< orphan*/  m_fdListen; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_Init_Prefork_Server (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LSAPI_Is_Listen () ; 
 int /*<<< orphan*/  LSAPI_No_Check_ppid () ; 
 int /*<<< orphan*/  LSAPI_Set_Extra_Children (void*) ; 
 int /*<<< orphan*/  LSAPI_Set_Max_Idle (int) ; 
 int /*<<< orphan*/  LSAPI_Set_Max_Idle_Children (void*) ; 
 int /*<<< orphan*/  LSAPI_Set_Max_Process_Time (void*) ; 
 int /*<<< orphan*/  LSAPI_Set_Max_Reqs (int) ; 
 int /*<<< orphan*/  LSAPI_Set_Server_Max_Idle_Secs (void*) ; 
 int /*<<< orphan*/  LSAPI_Set_Server_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSAPI_Set_Slow_Req_Msecs (int) ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 void* atoi (char const*) ; 
 TYPE_1__ g_req ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  isPipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsapi_initLVE () ; 
 int lsapi_initSuEXEC () ; 
 int /*<<< orphan*/  lsapi_reopen_stderr (char const*) ; 
 void* s_accept_notify ; 
 void* s_dump_debug_info ; 
 int s_enable_core_dump ; 
 int s_keepListener ; 
 int s_max_busy_workers ; 
 int s_min_avail_pages ; 
 int /*<<< orphan*/  s_stderr_is_pipe ; 
 int /*<<< orphan*/  s_stderr_log_path ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  unset_lsapi_envs () ; 

int LSAPI_Init_Env_Parameters( fn_select_t fp )
{
    const char *p;
    char ch;
    int n;
    int avoidFork = 0;

    p = getenv("LSAPI_STDERR_LOG");
    if (p)
    {
        lsapi_reopen_stderr(p);
    }
    if (!s_stderr_log_path)
        s_stderr_is_pipe = isPipe(STDERR_FILENO);

    p = getenv( "PHP_LSAPI_MAX_REQUESTS" );
    if ( !p )
        p = getenv( "LSAPI_MAX_REQS" );
    if ( p )
    {
        n = atoi( p );
        if ( n > 0 )
            LSAPI_Set_Max_Reqs( n );
    }

    p = getenv( "LSAPI_KEEP_LISTEN" );
    if ( p )
    {
        n = atoi( p );
        s_keepListener = n;
    }

    p = getenv( "LSAPI_AVOID_FORK" );
    if ( p )
    {
        avoidFork = atoi( p );
        if (avoidFork)
        {
            s_keepListener = 2;
            ch = *(p + strlen(p) - 1);
            if (  ch == 'G' || ch == 'g' )
                avoidFork *= 1024 * 1024 * 1024;
            else if (  ch == 'M' || ch == 'm' )
                avoidFork *= 1024 * 1024;
            if (avoidFork >= 1024 * 10240)
                s_min_avail_pages = avoidFork / 4096;
        }
    }

    p = getenv( "LSAPI_ACCEPT_NOTIFY" );
    if ( p )
    {
        s_accept_notify = atoi( p );
    }

    p = getenv( "LSAPI_SLOW_REQ_MSECS" );
    if ( p )
    {
        n = atoi( p );
        LSAPI_Set_Slow_Req_Msecs( n );
    }

#if defined( RLIMIT_CORE )
    p = getenv( "LSAPI_ALLOW_CORE_DUMP" );
    if ( !p )
    {
        struct rlimit limit = { 0, 0 };
        setrlimit( RLIMIT_CORE, &limit );
    }
    else
        s_enable_core_dump = 1;

#endif

    p = getenv( "LSAPI_MAX_IDLE" );
    if ( p )
    {
        n = atoi( p );
        LSAPI_Set_Max_Idle( n );
    }

    if ( LSAPI_Is_Listen() )
    {
        n = 0;
        p = getenv( "PHP_LSAPI_CHILDREN" );
        if ( !p )
            p = getenv( "LSAPI_CHILDREN" );
        if ( p )
            n = atoi( p );
        if ( n > 1 )
        {
            LSAPI_Init_Prefork_Server( n, fp, avoidFork != 0 );
            LSAPI_Set_Server_fd( g_req.m_fdListen );
        }

        p = getenv( "LSAPI_EXTRA_CHILDREN" );
        if ( p )
            LSAPI_Set_Extra_Children( atoi( p ) );

        p = getenv( "LSAPI_MAX_IDLE_CHILDREN" );
        if ( p )
            LSAPI_Set_Max_Idle_Children( atoi( p ) );

        p = getenv( "LSAPI_PGRP_MAX_IDLE" );
        if ( p )
        {
            LSAPI_Set_Server_Max_Idle_Secs( atoi( p ) );
        }

        p = getenv( "LSAPI_MAX_PROCESS_TIME" );
        if ( p )
            LSAPI_Set_Max_Process_Time( atoi( p ) );

        if ( getenv( "LSAPI_PPID_NO_CHECK" ) )
        {
            LSAPI_No_Check_ppid();
        }

        p = getenv("LSAPI_MAX_BUSY_WORKER");
        if (p)
        {
            n = atoi(p);
            s_max_busy_workers = n;
            if (n >= 0)
                LSAPI_No_Check_ppid();
        }


        p = getenv( "LSAPI_DUMP_DEBUG_INFO" );
        if ( p )
            s_dump_debug_info = atoi( p );

        if ( lsapi_initSuEXEC() == -1 )
            return -1;
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
        lsapi_initLVE();
#endif
    }
    unset_lsapi_envs();
    return 0;
}