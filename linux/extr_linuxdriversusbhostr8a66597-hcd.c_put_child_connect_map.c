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
struct r8a66597 {int* child_connect_map; } ;

/* Variables and functions */

__attribute__((used)) static void put_child_connect_map(struct r8a66597 *r8a66597, int address)
{
	int idx;

	idx = address / 32;
	r8a66597->child_connect_map[idx] &= ~(1 << (address % 32));
}