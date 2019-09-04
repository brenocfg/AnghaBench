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
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 scalar_t__ ifindex_to_name_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_string_field (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  jsonw_uint_field (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void print_dev_json(__u32 ifindex, __u64 ns_dev, __u64 ns_inode)
{
	char name[IF_NAMESIZE];

	if (!ifindex)
		return;

	jsonw_name(json_wtr, "dev");
	jsonw_start_object(json_wtr);
	jsonw_uint_field(json_wtr, "ifindex", ifindex);
	jsonw_uint_field(json_wtr, "ns_dev", ns_dev);
	jsonw_uint_field(json_wtr, "ns_inode", ns_inode);
	if (ifindex_to_name_ns(ifindex, ns_dev, ns_inode, name))
		jsonw_string_field(json_wtr, "ifname", name);
	jsonw_end_object(json_wtr);
}