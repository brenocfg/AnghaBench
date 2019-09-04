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
struct intel_vss {int dummy; } ;
struct ep_name_entry {int len; scalar_t__ type; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ EP_NAME_INTEL_VSS ; 

__attribute__((used)) static const struct intel_vss *parse_intel_vss(const void *ep_name, size_t size)
{
	const void *end = ep_name + size;

	while (ep_name < end) {
		const struct ep_name_entry *ep = ep_name;

		if (!ep->len)
			break;
		if (ep_name + ep->len > end)
			break;

		if (ep->type == EP_NAME_INTEL_VSS)
			return (const struct intel_vss *)ep->data;

		ep_name += ep->len;
	}

	return NULL;
}