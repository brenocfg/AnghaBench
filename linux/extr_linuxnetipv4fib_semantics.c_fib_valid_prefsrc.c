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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  nl_net; } ;
struct fib_config {int fc_type; scalar_t__ fc_dst; scalar_t__ fc_table; TYPE_1__ fc_nlinfo; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int RTN_LOCAL ; 
 scalar_t__ RT_TABLE_LOCAL ; 
 scalar_t__ RT_TABLE_MAIN ; 
 int inet_addr_type_table (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool fib_valid_prefsrc(struct fib_config *cfg, __be32 fib_prefsrc)
{
	if (cfg->fc_type != RTN_LOCAL || !cfg->fc_dst ||
	    fib_prefsrc != cfg->fc_dst) {
		u32 tb_id = cfg->fc_table;
		int rc;

		if (tb_id == RT_TABLE_MAIN)
			tb_id = RT_TABLE_LOCAL;

		rc = inet_addr_type_table(cfg->fc_nlinfo.nl_net,
					  fib_prefsrc, tb_id);

		if (rc != RTN_LOCAL && tb_id != RT_TABLE_LOCAL) {
			rc = inet_addr_type_table(cfg->fc_nlinfo.nl_net,
						  fib_prefsrc, RT_TABLE_LOCAL);
		}

		if (rc != RTN_LOCAL)
			return false;
	}
	return true;
}