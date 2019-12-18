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
struct openvpn_sockaddr {int /*<<< orphan*/  addr; } ;

/* Variables and functions */

__attribute__((used)) static inline void
addr_copy_sa(struct openvpn_sockaddr *dst, const struct openvpn_sockaddr *src)
{
    dst->addr = src->addr;
}