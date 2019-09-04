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
struct tun_struct {int flags; } ;

/* Variables and functions */
 int TUN_VNET_LE ; 
 scalar_t__ tun_legacy_is_little_endian (struct tun_struct*) ; 

__attribute__((used)) static inline bool tun_is_little_endian(struct tun_struct *tun)
{
	return tun->flags & TUN_VNET_LE ||
		tun_legacy_is_little_endian(tun);
}