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
struct hash_netportnet4_elem {int /*<<< orphan*/  port; int /*<<< orphan*/  ipcmp; } ;

/* Variables and functions */

__attribute__((used)) static inline void
hash_netportnet4_data_next(struct hash_netportnet4_elem *next,
			   const struct hash_netportnet4_elem *d)
{
	next->ipcmp = d->ipcmp;
	next->port = d->port;
}