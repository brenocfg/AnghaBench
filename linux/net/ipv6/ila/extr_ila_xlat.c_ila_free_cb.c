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
struct ila_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ila_free_node (struct ila_map*) ; 

__attribute__((used)) static void ila_free_cb(void *ptr, void *arg)
{
	ila_free_node((struct ila_map *)ptr);
}