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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; } ;
union socket_address {TYPE_2__ sin; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int inet_addr (char*) ; 
 int /*<<< orphan*/  memset (union socket_address*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_resolve_from_hosts_file (char*,union socket_address*) ; 

__attribute__((used)) static const char *test_dns_resolve_hosts(void) {
  union socket_address sa;
  in_addr_t want_addr = inet_addr("127.0.0.1");

  memset(&sa, 0, sizeof(sa));
  ASSERT_EQ(mg_resolve_from_hosts_file("localhost", &sa), 0);
  ASSERT_EQ(sa.sin.sin_addr.s_addr, want_addr);
  ASSERT_EQ(mg_resolve_from_hosts_file("does_not,exist!in_host*file", &sa), -1);

  return NULL;
}