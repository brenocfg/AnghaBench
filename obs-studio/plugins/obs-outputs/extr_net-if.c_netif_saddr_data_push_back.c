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
struct netif_saddr_item {char* addr; int /*<<< orphan*/  name; } ;
struct netif_saddr_data {int /*<<< orphan*/  addrs; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 char* bstrdup (char const*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct netif_saddr_item*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,char const*,char const*) ; 

__attribute__((used)) static inline void netif_saddr_data_push_back(struct netif_saddr_data *sd,
					      const char *ip,
					      const char *adapter)
{
	struct netif_saddr_item item;
	struct dstr full_name = {0};
	char *ip_dup = bstrdup(ip);

	if (adapter && *adapter)
		dstr_printf(&full_name, "[%s] %s", adapter, ip);
	else
		dstr_copy(&full_name, ip);

	item.name = full_name.array;
	item.addr = ip_dup;

	da_push_back(sd->addrs, &item);
}