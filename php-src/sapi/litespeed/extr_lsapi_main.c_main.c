#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; int tv_usec; } ;
struct TYPE_7__ {int /*<<< orphan*/ * path_translated; } ;
struct TYPE_6__ {int phpinfo_as_text; char* executable_location; int php_ini_ignore; char* php_ini_path_override; int /*<<< orphan*/  ini_defaults; } ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int LSAPI_CreateListenSock (char*,int) ; 
 int /*<<< orphan*/  LSAPI_Finish () ; 
 char* LSAPI_GetQueryString () ; 
 char* LSAPI_GetRequestMethod () ; 
 char* LSAPI_GetScriptFileName () ; 
 char* LSAPI_GetScriptName () ; 
 int LSAPI_Get_Slow_Req_Msecs () ; 
 int /*<<< orphan*/  LSAPI_Init () ; 
 int /*<<< orphan*/  LSAPI_Init_Env_Parameters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LSAPI_No_Check_ppid () ; 
 int LSAPI_Prefork_Accept_r (int /*<<< orphan*/ *) ; 
 int LSCRIU_Init () ; 
 int /*<<< orphan*/  LSCRIU_inc_req_procssed () ; 
 TYPE_5__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int cli_main (int,char**) ; 
 int /*<<< orphan*/  close (int) ; 
 void* compiler_globals ; 
 int /*<<< orphan*/  compiler_globals_id ; 
 void* core_globals ; 
 int /*<<< orphan*/  core_globals_id ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 void* executor_globals ; 
 int /*<<< orphan*/  executor_globals_id ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_req ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ ignore_php_ini ; 
 int /*<<< orphan*/  init_sapi_from_env (TYPE_1__*) ; 
 int /*<<< orphan*/  litespeed_module_entry ; 
 int /*<<< orphan*/  localtime (long*) ; 
 int /*<<< orphan*/  lsapi_atexit ; 
 int lsapi_mode ; 
 TYPE_1__ lsapi_sapi_module ; 
 int parse_opt (int,char**,int*,char**,char**) ; 
 int /*<<< orphan*/  php_module_shutdown () ; 
 scalar_t__ php_module_startup (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  php_tsrm_startup () ; 
 int processReq () ; 
 int /*<<< orphan*/  request_info ; 
 void* sapi_globals ; 
 int /*<<< orphan*/  sapi_globals_id ; 
 int /*<<< orphan*/  sapi_lsapi_ini_defaults ; 
 int /*<<< orphan*/  sapi_startup (TYPE_1__*) ; 
 int /*<<< orphan*/  setArgv0 (int,char**) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 void* ts_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsrm_shutdown () ; 
 int /*<<< orphan*/  zend_signal_startup () ; 

int main( int argc, char * argv[] )
{
    int ret;
    int bindFd;

    char * php_ini_path = NULL;
    char * php_bind     = NULL;
    int n;
    int climode = 0;
    struct timeval tv_req_begin;
    struct timeval tv_req_end;
    int slow_script_msec = 0;
    char time_buf[40];


#if defined(SIGPIPE) && defined(SIG_IGN)
    signal(SIGPIPE, SIG_IGN);
#endif

#ifdef ZTS
    php_tsrm_startup();
#endif

#if PHP_MAJOR_VERSION >= 7
#if defined(ZEND_SIGNALS) || PHP_MINOR_VERSION > 0
    zend_signal_startup();
#endif
#endif

    if (argc > 1 ) {
        if ( parse_opt( argc, argv, &climode,
                &php_ini_path, &php_bind ) == -1 ) {
            return 1;
        }
    }
    if ( climode ) {
        lsapi_sapi_module.phpinfo_as_text = 1;
    } else {
        setArgv0(argc, argv );
    }

    sapi_startup(&lsapi_sapi_module);

#ifdef ZTS
    compiler_globals = ts_resource(compiler_globals_id);
    executor_globals = ts_resource(executor_globals_id);
    core_globals = ts_resource(core_globals_id);
    sapi_globals = ts_resource(sapi_globals_id);

    SG(request_info).path_translated = NULL;
#endif

    lsapi_sapi_module.executable_location = argv[0];

    /* Initialize from environment variables before processing command-line
     * options: the latter override the former.
     */
    init_sapi_from_env(&lsapi_sapi_module);

    if ( ignore_php_ini )
        lsapi_sapi_module.php_ini_ignore = 1;

    if ( php_ini_path ) {
        lsapi_sapi_module.php_ini_path_override = php_ini_path;
    }


    lsapi_sapi_module.ini_defaults = sapi_lsapi_ini_defaults;

    if (php_module_startup(&lsapi_sapi_module, &litespeed_module_entry, 1) == FAILURE) {
#ifdef ZTS
        tsrm_shutdown();
#endif
        return FAILURE;
    }

    if ( climode ) {
        return cli_main(argc, argv);
    }

    if ( php_bind ) {
        bindFd = LSAPI_CreateListenSock( php_bind, 10 );
        if ( bindFd == -1 ) {
            fprintf( stderr,
                     "Failed to bind socket [%s]: %s\n", php_bind, strerror( errno ) );
            exit( 2 );
        }
        if ( bindFd != 0 ) {
            dup2( bindFd, 0 );
            close( bindFd );
        }
    }

    LSAPI_Init();

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
    int is_criu = LSCRIU_Init(); // Must be called before the regular init as it unsets the parameters.
#endif

    LSAPI_Init_Env_Parameters( NULL );
    lsapi_mode = 1;

    slow_script_msec = LSAPI_Get_Slow_Req_Msecs();

    if ( php_bind ) {
        LSAPI_No_Check_ppid();
        free( php_bind );
        php_bind = NULL;
    }

    int result;

    atexit(lsapi_atexit);

    while( ( result = LSAPI_Prefork_Accept_r( &g_req )) >= 0 ) {
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
        if (is_criu && !result) {
            LSCRIU_inc_req_procssed();
        }
#endif
        if ( slow_script_msec ) {
            gettimeofday( &tv_req_begin, NULL );
        }
        ret = processReq();
        if ( slow_script_msec ) {
            gettimeofday( &tv_req_end, NULL );
            n = ((long) tv_req_end.tv_sec - tv_req_begin.tv_sec ) * 1000
                + (tv_req_end.tv_usec - tv_req_begin.tv_usec) / 1000;
            if ( n > slow_script_msec )
            {
                strftime( time_buf, 30, "%d/%b/%Y:%H:%M:%S", localtime( &tv_req_end.tv_sec ) );
                fprintf( stderr, "[%s] Slow PHP script: %d ms\n  URL: %s %s\n  Query String: %s\n  Script: %s\n",
                         time_buf, n,  LSAPI_GetRequestMethod(),
                         LSAPI_GetScriptName(), LSAPI_GetQueryString(),
                         LSAPI_GetScriptFileName() );

            }
        }
        LSAPI_Finish();
        if ( ret ) {
            break;
        }
    }

    php_module_shutdown();

#ifdef ZTS
    tsrm_shutdown();
#endif
    return ret;
}