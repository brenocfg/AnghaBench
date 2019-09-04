#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_8__ {scalar_t__ kill_signal; } ;
typedef  TYPE_3__ ngx_rtmp_exec_main_conf_t ;
struct TYPE_9__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_6__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ SIGABRT ; 
 scalar_t__ SIGALRM ; 
 scalar_t__ SIGCHLD ; 
 scalar_t__ SIGCONT ; 
 scalar_t__ SIGFPE ; 
 scalar_t__ SIGHUP ; 
 scalar_t__ SIGILL ; 
 scalar_t__ SIGINT ; 
 scalar_t__ SIGKILL ; 
 scalar_t__ SIGPIPE ; 
 scalar_t__ SIGQUIT ; 
 scalar_t__ SIGSEGV ; 
 scalar_t__ SIGSTOP ; 
 scalar_t__ SIGTERM ; 
 scalar_t__ SIGTSTP ; 
 scalar_t__ SIGTTIN ; 
 scalar_t__ SIGTTOU ; 
 scalar_t__ SIGUSR1 ; 
 scalar_t__ SIGUSR2 ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
ngx_rtmp_exec_kill_signal(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_exec_main_conf_t  *emcf = conf;

    ngx_str_t  *value;

    value = cf->args->elts;
    value++;

    emcf->kill_signal = ngx_atoi(value->data, value->len);
    if (emcf->kill_signal != NGX_ERROR) {
        return NGX_CONF_OK;
    }

#define NGX_RMTP_EXEC_SIGNAL(name)                                          \
    if (value->len == sizeof(#name) - 1 &&                                  \
        ngx_strncasecmp(value->data, (u_char *) #name, value->len) == 0)    \
    {                                                                       \
        emcf->kill_signal = SIG##name;                                      \
        return NGX_CONF_OK;                                                 \
    }

    /* POSIX.1-1990 signals */

#if !(NGX_WIN32)
    NGX_RMTP_EXEC_SIGNAL(HUP);
    NGX_RMTP_EXEC_SIGNAL(INT);
    NGX_RMTP_EXEC_SIGNAL(QUIT);
    NGX_RMTP_EXEC_SIGNAL(ILL);
    NGX_RMTP_EXEC_SIGNAL(ABRT);
    NGX_RMTP_EXEC_SIGNAL(FPE);
    NGX_RMTP_EXEC_SIGNAL(KILL);
    NGX_RMTP_EXEC_SIGNAL(SEGV);
    NGX_RMTP_EXEC_SIGNAL(PIPE);
    NGX_RMTP_EXEC_SIGNAL(ALRM);
    NGX_RMTP_EXEC_SIGNAL(TERM);
    NGX_RMTP_EXEC_SIGNAL(USR1);
    NGX_RMTP_EXEC_SIGNAL(USR2);
    NGX_RMTP_EXEC_SIGNAL(CHLD);
    NGX_RMTP_EXEC_SIGNAL(CONT);
    NGX_RMTP_EXEC_SIGNAL(STOP);
    NGX_RMTP_EXEC_SIGNAL(TSTP);
    NGX_RMTP_EXEC_SIGNAL(TTIN);
    NGX_RMTP_EXEC_SIGNAL(TTOU);
#endif

#undef NGX_RMTP_EXEC_SIGNAL

    return "unknown signal";
}