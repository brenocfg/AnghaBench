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
struct sw_flow_id {int ufid_len; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ovs_identifier_is_ufid(const struct sw_flow_id *sfid)
{
	return sfid->ufid_len;
}