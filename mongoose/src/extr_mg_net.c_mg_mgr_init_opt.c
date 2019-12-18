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
struct mg_mgr_init_opts {int num_ifaces; int /*<<< orphan*/ * nameserver; int /*<<< orphan*/ ** ifaces; int /*<<< orphan*/ * main_iface; } ;
struct mg_mgr {int num_ifaces; int /*<<< orphan*/  nameserver; struct mg_iface** ifaces; void* user_data; int /*<<< orphan*/ * ctl; } ;
struct mg_iface {TYPE_1__* vtable; } ;
typedef  int /*<<< orphan*/  WSADATA ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct mg_iface*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 size_t MG_MAIN_IFACE ; 
 scalar_t__ MG_MALLOC (int) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mg_mgr*,int /*<<< orphan*/ ,int) ; 
 struct mg_iface* mg_if_create_iface (int /*<<< orphan*/ *,struct mg_mgr*) ; 
 int /*<<< orphan*/ ** mg_ifaces ; 
 int mg_num_ifaces ; 
 int /*<<< orphan*/  mg_ssl_if_init () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mg_iface*) ; 

void mg_mgr_init_opt(struct mg_mgr *m, void *user_data,
                     struct mg_mgr_init_opts opts) {
  memset(m, 0, sizeof(*m));
#if MG_ENABLE_BROADCAST
  m->ctl[0] = m->ctl[1] = INVALID_SOCKET;
#endif
  m->user_data = user_data;

#ifdef _WIN32
  {
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
  }
#elif defined(__unix__)
  /* Ignore SIGPIPE signal, so if client cancels the request, it
   * won't kill the whole process. */
  signal(SIGPIPE, SIG_IGN);
#endif

  {
    int i;
    if (opts.num_ifaces == 0) {
      opts.num_ifaces = mg_num_ifaces;
      opts.ifaces = mg_ifaces;
    }
    if (opts.main_iface != NULL) {
      opts.ifaces[MG_MAIN_IFACE] = opts.main_iface;
    }
    m->num_ifaces = opts.num_ifaces;
    m->ifaces =
        (struct mg_iface **) MG_MALLOC(sizeof(*m->ifaces) * opts.num_ifaces);
    for (i = 0; i < opts.num_ifaces; i++) {
      m->ifaces[i] = mg_if_create_iface(opts.ifaces[i], m);
      m->ifaces[i]->vtable->init(m->ifaces[i]);
    }
  }
  if (opts.nameserver != NULL) {
    m->nameserver = strdup(opts.nameserver);
  }
  DBG(("=================================="));
  DBG(("init mgr=%p", m));
#if MG_ENABLE_SSL
  {
    static int init_done;
    if (!init_done) {
      mg_ssl_if_init();
      init_done++;
    }
  }
#endif
}