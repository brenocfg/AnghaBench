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
struct in_ifaddr {int dummy; } ;

/* Variables and functions */
 int __inet_insert_ifa (struct in_ifaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inet_insert_ifa(struct in_ifaddr *ifa)
{
	return __inet_insert_ifa(ifa, NULL, 0, NULL);
}