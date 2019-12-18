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
typedef  int /*<<< orphan*/  block_info ;

/* Variables and functions */

__attribute__((used)) static void swap_blocks(block_info *a, block_info *b) {
	block_info tmp = *a;
	*a = *b;
	*b = tmp;
}