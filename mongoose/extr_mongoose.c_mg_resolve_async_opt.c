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
struct mg_resolve_async_request {char* name; int query; int max_retries; int timeout; void* data; int /*<<< orphan*/  callback; } ;
struct mg_resolve_async_opts {char* nameserver; int max_retries; int timeout; struct mg_connection** dns_conn; } ;
struct mg_mgr {char* nameserver; } ;
struct mg_connection {struct mg_resolve_async_request* user_data; } ;
typedef  int /*<<< orphan*/  nameserver_url ;
typedef  int /*<<< orphan*/  mg_resolve_callback_t ;
typedef  int /*<<< orphan*/  dns_server_buff ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ MG_CALLOC (int,int) ; 
 int /*<<< orphan*/  MG_CB (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* MG_DEFAULT_NAMESERVER ; 
 int /*<<< orphan*/  MG_FREE (struct mg_resolve_async_request*) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int mg_get_ip_address_of_nameserver (char*,int) ; 
 int /*<<< orphan*/  mg_resolve_async_eh ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int mg_resolve_async_opt(struct mg_mgr *mgr, const char *name, int query,
                         mg_resolve_callback_t cb, void *data,
                         struct mg_resolve_async_opts opts) {
  struct mg_resolve_async_request *req;
  struct mg_connection *dns_nc;
  const char *nameserver = opts.nameserver;
  char dns_server_buff[17], nameserver_url[26];

  if (nameserver == NULL) {
    nameserver = mgr->nameserver;
  }

  DBG(("%s %d %p", name, query, opts.dns_conn));

  /* resolve with DNS */
  req = (struct mg_resolve_async_request *) MG_CALLOC(1, sizeof(*req));
  if (req == NULL) {
    return -1;
  }

  strncpy(req->name, name, sizeof(req->name));
  req->name[sizeof(req->name) - 1] = '\0';

  req->query = query;
  req->callback = cb;
  req->data = data;
  /* TODO(mkm): parse defaults out of resolve.conf */
  req->max_retries = opts.max_retries ? opts.max_retries : 2;
  req->timeout = opts.timeout ? opts.timeout : 5;

  /* Lazily initialize dns server */
  if (nameserver == NULL) {
    if (mg_get_ip_address_of_nameserver(dns_server_buff,
                                        sizeof(dns_server_buff)) != -1) {
      nameserver = dns_server_buff;
    } else {
      nameserver = MG_DEFAULT_NAMESERVER;
    }
  }

  snprintf(nameserver_url, sizeof(nameserver_url), "udp://%s:53", nameserver);

  dns_nc = mg_connect(mgr, nameserver_url, MG_CB(mg_resolve_async_eh, NULL));
  if (dns_nc == NULL) {
    MG_FREE(req);
    return -1;
  }
  dns_nc->user_data = req;
  if (opts.dns_conn != NULL) {
    *opts.dns_conn = dns_nc;
  }

  return 0;
}