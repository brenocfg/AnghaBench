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
struct mg_resolve_async_opts {char* nameserver; int timeout; int max_retries; } ;
struct mg_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  MG_DNS_A_RECORD ; 
 int /*<<< orphan*/  c_int_eq ; 
 int /*<<< orphan*/  dns_resolve_timeout_cb ; 
 int /*<<< orphan*/  memset (struct mg_resolve_async_opts*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_resolve_async_opt (struct mg_mgr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct mg_resolve_async_opts) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int*,void*) ; 

__attribute__((used)) static const char *test_dns_resolve_timeout(void) {
  struct mg_mgr mgr;
  struct mg_resolve_async_opts opts;
  int data = 0;
  mg_mgr_init(&mgr, NULL);
  memset(&opts, 0, sizeof(opts));

  opts.nameserver = "7.7.7.7";
  opts.timeout = -1; /* 0 would be the default timeout */
  opts.max_retries = 1;
  mg_resolve_async_opt(&mgr, "www.cesanta.com", MG_DNS_A_RECORD,
                       dns_resolve_timeout_cb, &data, opts);

  poll_until(&mgr, 5, c_int_eq, &data, (void *) 1);
  ASSERT_EQ(data, 1);

  mg_mgr_free(&mgr);
  return NULL;
}