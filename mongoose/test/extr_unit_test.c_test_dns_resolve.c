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
struct mg_mgr_init_opts {char* nameserver; } ;
struct mg_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  MG_DNS_A_RECORD ; 
 int /*<<< orphan*/  c_int_ne ; 
 int /*<<< orphan*/  dns_resolve_cb ; 
 int /*<<< orphan*/  memset (struct mg_mgr_init_opts*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_init_opt (struct mg_mgr*,int /*<<< orphan*/ *,struct mg_mgr_init_opts) ; 
 int /*<<< orphan*/  mg_resolve_async (struct mg_mgr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mg_set_nameserver (struct mg_mgr*,char*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int*,void*) ; 

__attribute__((used)) static const char *test_dns_resolve(void) {
  struct mg_mgr mgr;
  struct mg_mgr_init_opts opts;

  int data = 0;

  mg_mgr_init(&mgr, NULL);

  /* Microsoft promises dns.msftncsi.com is always 131.107.255.255 */
  mg_resolve_async(&mgr, "dns.msftncsi.com", MG_DNS_A_RECORD, dns_resolve_cb,
                   &data);

  poll_until(&mgr, 1, c_int_ne, &data, (void *) 0);
  ASSERT_EQ(data, 1);

  mg_mgr_free(&mgr);

  data = 0;
  memset(&opts, 0, sizeof(opts));
  opts.nameserver = "8.8.4.4";
  mg_mgr_init_opt(&mgr, NULL, opts);

  /* Microsoft promises dns.msftncsi.com is always 131.107.255.255 */
  mg_resolve_async(&mgr, "dns.msftncsi.com", MG_DNS_A_RECORD, dns_resolve_cb,
                   &data);

  poll_until(&mgr, 1, c_int_ne, &data, (void *) 0);
  ASSERT_EQ(data, 1);

  mg_mgr_free(&mgr);

  data = 0;
  mg_mgr_init(&mgr, NULL);
  mg_set_nameserver(&mgr, "8.8.4.4");

  /* Microsoft promises dns.msftncsi.com is always 131.107.255.255 */
  mg_resolve_async(&mgr, "dns.msftncsi.com", MG_DNS_A_RECORD, dns_resolve_cb,
                   &data);

  poll_until(&mgr, 1, c_int_ne, &data, (void *) 0);
  ASSERT_EQ(data, 1);

  mg_mgr_free(&mgr);

  return NULL;
}