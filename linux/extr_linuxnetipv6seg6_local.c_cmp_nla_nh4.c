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
struct seg6_local_lwt {int /*<<< orphan*/  nh4; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmp_nla_nh4(struct seg6_local_lwt *a, struct seg6_local_lwt *b)
{
	return memcmp(&a->nh4, &b->nh4, sizeof(struct in_addr));
}