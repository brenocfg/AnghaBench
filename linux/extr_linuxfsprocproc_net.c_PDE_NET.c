#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {TYPE_1__* parent; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct net* data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct net *PDE_NET(struct proc_dir_entry *pde)
{
	return pde->parent->data;
}