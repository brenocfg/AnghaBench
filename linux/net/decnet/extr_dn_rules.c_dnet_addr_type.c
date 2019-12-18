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
struct flowidn {int /*<<< orphan*/  daddr; } ;
struct dn_fib_table {int /*<<< orphan*/  (* lookup ) (struct dn_fib_table*,struct flowidn*,struct dn_fib_res*) ;} ;
struct dn_fib_res {unsigned int type; int /*<<< orphan*/ * r; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 unsigned int RTN_UNICAST ; 
 int /*<<< orphan*/  RT_TABLE_LOCAL ; 
 struct dn_fib_table* dn_fib_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_fib_res_put (struct dn_fib_res*) ; 
 int /*<<< orphan*/  stub1 (struct dn_fib_table*,struct flowidn*,struct dn_fib_res*) ; 

unsigned int dnet_addr_type(__le16 addr)
{
	struct flowidn fld = { .daddr = addr };
	struct dn_fib_res res;
	unsigned int ret = RTN_UNICAST;
	struct dn_fib_table *tb = dn_fib_get_table(RT_TABLE_LOCAL, 0);

	res.r = NULL;

	if (tb) {
		if (!tb->lookup(tb, &fld, &res)) {
			ret = res.type;
			dn_fib_res_put(&res);
		}
	}
	return ret;
}