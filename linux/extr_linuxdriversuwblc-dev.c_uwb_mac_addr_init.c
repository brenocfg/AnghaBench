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
struct uwb_mac_addr {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void uwb_mac_addr_init(struct uwb_mac_addr *addr)
{
	memset(&addr->data, 0xff, sizeof(addr->data));
}