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
struct sw_flow_id {int ufid_len; int /*<<< orphan*/  ufid; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int get_ufid_len (struct nlattr const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 

bool ovs_nla_get_ufid(struct sw_flow_id *sfid, const struct nlattr *attr,
		      bool log)
{
	sfid->ufid_len = get_ufid_len(attr, log);
	if (sfid->ufid_len)
		memcpy(sfid->ufid, nla_data(attr), sfid->ufid_len);

	return sfid->ufid_len;
}