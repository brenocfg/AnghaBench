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
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nla_get_u32 (struct nlattr const*) ; 

u32 ovs_nla_get_ufid_flags(const struct nlattr *attr)
{
	return attr ? nla_get_u32(attr) : 0;
}