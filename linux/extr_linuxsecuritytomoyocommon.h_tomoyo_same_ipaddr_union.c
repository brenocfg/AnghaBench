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
struct tomoyo_ipaddr_union {scalar_t__ group; scalar_t__ is_ipv6; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool tomoyo_same_ipaddr_union
(const struct tomoyo_ipaddr_union *a, const struct tomoyo_ipaddr_union *b)
{
	return !memcmp(a->ip, b->ip, sizeof(a->ip)) && a->group == b->group &&
		a->is_ipv6 == b->is_ipv6;
}