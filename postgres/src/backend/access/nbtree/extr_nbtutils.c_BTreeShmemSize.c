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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  BTOneVacInfo ;

/* Variables and functions */
 int /*<<< orphan*/  BTVacInfo ; 
 int /*<<< orphan*/  MaxBackends ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vacuums ; 

Size
BTreeShmemSize(void)
{
	Size		size;

	size = offsetof(BTVacInfo, vacuums);
	size = add_size(size, mul_size(MaxBackends, sizeof(BTOneVacInfo)));
	return size;
}