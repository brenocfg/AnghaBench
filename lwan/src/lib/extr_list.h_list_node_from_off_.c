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
struct list_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct list_node *list_node_from_off_(void *ptr, size_t off)
{
	return (struct list_node *)((char *)ptr + off);
}