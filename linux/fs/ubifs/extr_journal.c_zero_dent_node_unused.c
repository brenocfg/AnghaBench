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
struct ubifs_dent_node {scalar_t__ padding1; } ;

/* Variables and functions */

__attribute__((used)) static inline void zero_dent_node_unused(struct ubifs_dent_node *dent)
{
	dent->padding1 = 0;
}