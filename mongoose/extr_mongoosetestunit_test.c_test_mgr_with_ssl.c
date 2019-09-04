#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mg_mgr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_4__ {TYPE_1__ sin; } ;
struct mg_connection {char* user_data; int /*<<< orphan*/  sock; TYPE_2__ sa; } ;
struct mg_bind_opts {int dummy; } ;
typedef  int /*<<< orphan*/  short_addr ;
typedef  int /*<<< orphan*/  bopts ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  c_str_ne ; 
 int /*<<< orphan*/  eh1 ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mg_bind_opts*,int /*<<< orphan*/ ,int) ; 
 struct mg_connection* mg_bind_opt (struct mg_mgr*,char*,int /*<<< orphan*/ ,struct mg_bind_opts) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_sock_to_str (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,char*,void*) ; 
 int sscanf (char*,char*,char*,int*) ; 

__attribute__((used)) static const char *test_mgr_with_ssl(int use_ssl) {
  char addr[100] = "127.0.0.1:0", ip[sizeof(addr)], buf[100] = "",
       short_addr[5];
  struct mg_mgr mgr;
  struct mg_connection *nc;
  struct mg_bind_opts bopts;
  int port, port2;
#if !MG_ENABLE_SSL
  (void) use_ssl;
#endif

  mg_mgr_init(&mgr, NULL);
  /* mgr.hexdump_file = "-"; */

  memset(&bopts, 0, sizeof(bopts));
#if MG_ENABLE_SSL
  if (use_ssl) {
    bopts.ssl_cert = S_PEM;
    bopts.ssl_ca_cert = CA_PEM;
  }
#endif
  ASSERT((nc = mg_bind_opt(&mgr, addr, eh1, bopts)) != NULL);
  port2 = htons(nc->sa.sin.sin_port);
  ASSERT(port2 > 0);

  mg_sock_to_str(nc->sock, addr, sizeof(addr), 3);
  ASSERT_EQ(sscanf(addr, "%[^:]:%d", ip, &port), 2);
  ASSERT_STREQ(ip, "127.0.0.1");
  ASSERT_EQ(port, port2);

  mg_sock_to_str(nc->sock, short_addr, sizeof(short_addr), 3);
#ifndef _WIN32
  ASSERT_STREQ(short_addr, "");
#else
  /* We use `inet_ntoa` in Windows, so, can get partial result */
  ASSERT_STREQ(short_addr, "127.");
#endif

  ASSERT((nc = mg_connect(&mgr, addr, eh1)) != NULL);
#if MG_ENABLE_SSL
  if (use_ssl) {
    ASSERT(mg_set_ssl(nc, C_PEM, CA_PEM) == NULL);
  }
#endif
  nc->user_data = buf;
  poll_until(&mgr, 1, c_str_ne, buf, (void *) "");
  ASSERT_STREQ(buf, "ok!");
  buf[0] = '\0';

#if MG_ENABLE_SSL
  if (use_ssl) {
    struct mg_connect_opts opts;
    memset(&opts, 0, sizeof(opts));
    opts.user_data = buf;
    opts.ssl_cert = C_PEM;
    opts.ssl_ca_cert = CA_PEM;
    opts.ssl_server_name = "*"; /* TODO(rojer): Test this too. */
    ASSERT((nc = mg_connect_opt(&mgr, addr, eh1, opts)) != NULL);
    poll_until(&mgr, 1, c_str_ne, buf, (void *) "");
    ASSERT_STREQ(buf, "ok!");
    buf[0] = '\0';
  }
#endif

  mg_mgr_free(&mgr);
  return NULL;
}