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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {void* type; struct netlbl_domaddr_map* addrsel; struct cipso_v4_doi* cipso; } ;
struct TYPE_4__ {int addr; int mask; int valid; } ;
struct netlbl_domaddr_map {struct netlbl_domaddr_map* domain; TYPE_1__ def; int /*<<< orphan*/  list4; TYPE_2__ list; int /*<<< orphan*/  list6; int /*<<< orphan*/  family; } ;
struct netlbl_domaddr4_map {struct netlbl_domaddr4_map* domain; TYPE_1__ def; int /*<<< orphan*/  list4; TYPE_2__ list; int /*<<< orphan*/  list6; int /*<<< orphan*/  family; } ;
struct netlbl_dom_map {struct netlbl_dom_map* domain; TYPE_1__ def; int /*<<< orphan*/  list4; TYPE_2__ list; int /*<<< orphan*/  list6; int /*<<< orphan*/  family; } ;
struct netlbl_audit {int dummy; } ;
struct in_addr {int s_addr; } ;
struct cipso_v4_doi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* NETLBL_NLTYPE_ADDRSELECT ; 
 void* NETLBL_NLTYPE_CIPSOV4 ; 
 struct cipso_v4_doi* cipso_v4_doi_getdef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipso_v4_doi_putdef (struct cipso_v4_doi*) ; 
 int /*<<< orphan*/  kfree (struct netlbl_domaddr_map*) ; 
 struct netlbl_domaddr_map* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct netlbl_domaddr_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int netlbl_af4list_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int netlbl_domhsh_add (struct netlbl_domaddr_map*,struct netlbl_audit*) ; 

int netlbl_cfg_cipsov4_map_add(u32 doi,
			       const char *domain,
			       const struct in_addr *addr,
			       const struct in_addr *mask,
			       struct netlbl_audit *audit_info)
{
	int ret_val = -ENOMEM;
	struct cipso_v4_doi *doi_def;
	struct netlbl_dom_map *entry;
	struct netlbl_domaddr_map *addrmap = NULL;
	struct netlbl_domaddr4_map *addrinfo = NULL;

	doi_def = cipso_v4_doi_getdef(doi);
	if (doi_def == NULL)
		return -ENOENT;

	entry = kzalloc(sizeof(*entry), GFP_ATOMIC);
	if (entry == NULL)
		goto out_entry;
	entry->family = AF_INET;
	if (domain != NULL) {
		entry->domain = kstrdup(domain, GFP_ATOMIC);
		if (entry->domain == NULL)
			goto out_domain;
	}

	if (addr == NULL && mask == NULL) {
		entry->def.cipso = doi_def;
		entry->def.type = NETLBL_NLTYPE_CIPSOV4;
	} else if (addr != NULL && mask != NULL) {
		addrmap = kzalloc(sizeof(*addrmap), GFP_ATOMIC);
		if (addrmap == NULL)
			goto out_addrmap;
		INIT_LIST_HEAD(&addrmap->list4);
		INIT_LIST_HEAD(&addrmap->list6);

		addrinfo = kzalloc(sizeof(*addrinfo), GFP_ATOMIC);
		if (addrinfo == NULL)
			goto out_addrinfo;
		addrinfo->def.cipso = doi_def;
		addrinfo->def.type = NETLBL_NLTYPE_CIPSOV4;
		addrinfo->list.addr = addr->s_addr & mask->s_addr;
		addrinfo->list.mask = mask->s_addr;
		addrinfo->list.valid = 1;
		ret_val = netlbl_af4list_add(&addrinfo->list, &addrmap->list4);
		if (ret_val != 0)
			goto cfg_cipsov4_map_add_failure;

		entry->def.addrsel = addrmap;
		entry->def.type = NETLBL_NLTYPE_ADDRSELECT;
	} else {
		ret_val = -EINVAL;
		goto out_addrmap;
	}

	ret_val = netlbl_domhsh_add(entry, audit_info);
	if (ret_val != 0)
		goto cfg_cipsov4_map_add_failure;

	return 0;

cfg_cipsov4_map_add_failure:
	kfree(addrinfo);
out_addrinfo:
	kfree(addrmap);
out_addrmap:
	kfree(entry->domain);
out_domain:
	kfree(entry);
out_entry:
	cipso_v4_doi_putdef(doi_def);
	return ret_val;
}