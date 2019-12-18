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
struct l2tp_tunnel {int /*<<< orphan*/  sock; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* sk_dst_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 l2tp_tunnel_dst_mtu(const struct l2tp_tunnel *tunnel)
{
	struct dst_entry *dst;
	u32 mtu;

	dst = sk_dst_get(tunnel->sock);
	if (!dst)
		return 0;

	mtu = dst_mtu(dst);
	dst_release(dst);

	return mtu;
}