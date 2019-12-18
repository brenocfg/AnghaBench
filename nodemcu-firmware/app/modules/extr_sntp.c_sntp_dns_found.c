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
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNTP_DOLOOKUPS_ID ; 
 size_t server_count ; 
 int /*<<< orphan*/ * serverp ; 
 int /*<<< orphan*/  sntp_dbg (char*) ; 
 int /*<<< orphan*/  task_post_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasknumber ; 

__attribute__((used)) static void sntp_dns_found(const char *name, ip_addr_t *ipaddr, void *arg)
{
  (void)arg;

  if (ipaddr == NULL)
  {
    sntp_dbg("DNS Fail!\n");
  }
  else
  {
    serverp[server_count] = *ipaddr;
    server_count++;
  }
  task_post_low(tasknumber, SNTP_DOLOOKUPS_ID);
}