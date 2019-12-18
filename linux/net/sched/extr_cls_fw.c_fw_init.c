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
struct tcf_proto {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int fw_init(struct tcf_proto *tp)
{
	/* We don't allocate fw_head here, because in the old method
	 * we don't need it at all.
	 */
	return 0;
}