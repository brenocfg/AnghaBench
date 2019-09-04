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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static bool nf_generic_should_process(u8 proto)
{
	switch (proto) {
#ifdef CONFIG_NF_CT_PROTO_GRE_MODULE
	case IPPROTO_GRE:
		return false;
#endif
	default:
		return true;
	}
}