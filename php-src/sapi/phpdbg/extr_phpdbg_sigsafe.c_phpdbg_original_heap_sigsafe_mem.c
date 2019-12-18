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
typedef  int /*<<< orphan*/  zend_mm_heap ;
struct TYPE_2__ {int /*<<< orphan*/ * old_heap; } ;

/* Variables and functions */
 TYPE_1__ PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsafe_mem ; 

zend_mm_heap *phpdbg_original_heap_sigsafe_mem(void) {
	return PHPDBG_G(sigsafe_mem).old_heap;
}