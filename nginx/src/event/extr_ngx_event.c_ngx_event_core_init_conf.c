#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ type; TYPE_3__* ctx; int /*<<< orphan*/  ctx_index; } ;
typedef  TYPE_2__ ngx_module_t ;
typedef  size_t ngx_int_t ;
struct TYPE_15__ {TYPE_1__* name; } ;
typedef  TYPE_3__ ngx_event_module_t ;
struct TYPE_16__ {int /*<<< orphan*/  accept_mutex_delay; int /*<<< orphan*/  accept_mutex; int /*<<< orphan*/  multi_accept; int /*<<< orphan*/  name; int /*<<< orphan*/  use; int /*<<< orphan*/  connections; } ;
typedef  TYPE_4__ ngx_event_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/  connection_n; int /*<<< orphan*/  log; TYPE_2__** modules; } ;
typedef  TYPE_5__ ngx_cycle_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CONNECTIONS ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ENOSYS ; 
 scalar_t__ NGX_EVENT_MODULE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  close (int) ; 
 int epoll_create (int) ; 
 TYPE_11__ event_core_name ; 
 int /*<<< orphan*/  ngx_conf_init_msec_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_init_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_init_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_init_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ngx_devpoll_module ; 
 TYPE_2__ ngx_epoll_module ; 
 scalar_t__ ngx_errno ; 
 TYPE_2__ ngx_kqueue_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ ngx_select_module ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_event_core_init_conf(ngx_cycle_t *cycle, void *conf)
{
    ngx_event_conf_t  *ecf = conf;

#if (NGX_HAVE_EPOLL) && !(NGX_TEST_BUILD_EPOLL)
    int                  fd;
#endif
    ngx_int_t            i;
    ngx_module_t        *module;
    ngx_event_module_t  *event_module;

    module = NULL;

#if (NGX_HAVE_EPOLL) && !(NGX_TEST_BUILD_EPOLL)

    fd = epoll_create(100);

    if (fd != -1) {
        (void) close(fd);
        module = &ngx_epoll_module;

    } else if (ngx_errno != NGX_ENOSYS) {
        module = &ngx_epoll_module;
    }

#endif

#if (NGX_HAVE_DEVPOLL) && !(NGX_TEST_BUILD_DEVPOLL)

    module = &ngx_devpoll_module;

#endif

#if (NGX_HAVE_KQUEUE)

    module = &ngx_kqueue_module;

#endif

#if (NGX_HAVE_SELECT)

    if (module == NULL) {
        module = &ngx_select_module;
    }

#endif

    if (module == NULL) {
        for (i = 0; cycle->modules[i]; i++) {

            if (cycle->modules[i]->type != NGX_EVENT_MODULE) {
                continue;
            }

            event_module = cycle->modules[i]->ctx;

            if (ngx_strcmp(event_module->name->data, event_core_name.data) == 0)
            {
                continue;
            }

            module = cycle->modules[i];
            break;
        }
    }

    if (module == NULL) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, 0, "no events module found");
        return NGX_CONF_ERROR;
    }

    ngx_conf_init_uint_value(ecf->connections, DEFAULT_CONNECTIONS);
    cycle->connection_n = ecf->connections;

    ngx_conf_init_uint_value(ecf->use, module->ctx_index);

    event_module = module->ctx;
    ngx_conf_init_ptr_value(ecf->name, event_module->name->data);

    ngx_conf_init_value(ecf->multi_accept, 0);
    ngx_conf_init_value(ecf->accept_mutex, 0);
    ngx_conf_init_msec_value(ecf->accept_mutex_delay, 500);

    return NGX_CONF_OK;
}