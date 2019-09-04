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
typedef  int /*<<< orphan*/  uncond ;
struct ipt_ip {int dummy; } ;
struct ipt_entry {int target_offset; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct ipt_ip const*,int) ; 

__attribute__((used)) static inline bool unconditional(const struct ipt_entry *e)
{
	static const struct ipt_ip uncond;

	return e->target_offset == sizeof(struct ipt_entry) &&
	       memcmp(&e->ip, &uncond, sizeof(uncond)) == 0;
}