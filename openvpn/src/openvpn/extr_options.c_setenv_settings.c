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
struct options {int /*<<< orphan*/  ce; TYPE_1__* connection_list; int /*<<< orphan*/  log; int /*<<< orphan*/  daemon; int /*<<< orphan*/  verbosity; int /*<<< orphan*/  config; } ;
struct env_set {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ ** array; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_getpid () ; 
 int /*<<< orphan*/  setenv_connection_entry (struct env_set*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setenv_int (struct env_set*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv_long_long (struct env_set*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
setenv_settings(struct env_set *es, const struct options *o)
{
    setenv_str(es, "config", o->config);
    setenv_int(es, "verb", o->verbosity);
    setenv_int(es, "daemon", o->daemon);
    setenv_int(es, "daemon_log_redirect", o->log);
    setenv_long_long(es, "daemon_start_time", time(NULL));
    setenv_int(es, "daemon_pid", platform_getpid());

    if (o->connection_list)
    {
        int i;
        for (i = 0; i < o->connection_list->len; ++i)
        {
            setenv_connection_entry(es, o->connection_list->array[i], i+1);
        }
    }
    else
    {
        setenv_connection_entry(es, &o->ce, 1);
    }
}