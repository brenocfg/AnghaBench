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
struct ieee80211_reg_rule {int dummy; } ;
struct fwdb_header {struct fwdb_country* country; } ;
struct fwdb_country {int /*<<< orphan*/  alpha2; scalar_t__ coll_ptr; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ IS_ERR (struct fwdb_header*) ; 
 int PTR_ERR (struct fwdb_header*) ; 
 int __regdb_query_wmm (struct fwdb_header*,struct fwdb_country const*,int,struct ieee80211_reg_rule*) ; 
 scalar_t__ alpha2_equal (char*,int /*<<< orphan*/ ) ; 
 struct fwdb_header* regdb ; 

int reg_query_regdb_wmm(char *alpha2, int freq, struct ieee80211_reg_rule *rule)
{
	const struct fwdb_header *hdr = regdb;
	const struct fwdb_country *country;

	if (!regdb)
		return -ENODATA;

	if (IS_ERR(regdb))
		return PTR_ERR(regdb);

	country = &hdr->country[0];
	while (country->coll_ptr) {
		if (alpha2_equal(alpha2, country->alpha2))
			return __regdb_query_wmm(regdb, country, freq, rule);

		country++;
	}

	return -ENODATA;
}