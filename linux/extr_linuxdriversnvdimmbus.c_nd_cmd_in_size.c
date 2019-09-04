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
typedef  scalar_t__ u32 ;
struct nvdimm {int dummy; } ;
struct nd_cmd_vendor_hdr {scalar_t__ in_length; } ;
struct nd_cmd_set_config_hdr {scalar_t__ in_length; } ;
struct nd_cmd_pkg {scalar_t__ nd_size_in; } ;
struct nd_cmd_desc {int in_num; scalar_t__* in_sizes; } ;

/* Variables and functions */
 int ND_CMD_CALL ; 
 int ND_CMD_SET_CONFIG_DATA ; 
 int ND_CMD_VENDOR ; 
 scalar_t__ UINT_MAX ; 

u32 nd_cmd_in_size(struct nvdimm *nvdimm, int cmd,
		const struct nd_cmd_desc *desc, int idx, void *buf)
{
	if (idx >= desc->in_num)
		return UINT_MAX;

	if (desc->in_sizes[idx] < UINT_MAX)
		return desc->in_sizes[idx];

	if (nvdimm && cmd == ND_CMD_SET_CONFIG_DATA && idx == 2) {
		struct nd_cmd_set_config_hdr *hdr = buf;

		return hdr->in_length;
	} else if (nvdimm && cmd == ND_CMD_VENDOR && idx == 2) {
		struct nd_cmd_vendor_hdr *hdr = buf;

		return hdr->in_length;
	} else if (cmd == ND_CMD_CALL) {
		struct nd_cmd_pkg *pkg = buf;

		return pkg->nd_size_in;
	}

	return UINT_MAX;
}