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
struct in6_addr {int /*<<< orphan*/  s6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int is_v4inv6(const struct in6_addr *a) {
	return !memcmp(a->s6_addr, "\0\0\0\0\0\0\0\0\0\0\xff\xff", 12);
}