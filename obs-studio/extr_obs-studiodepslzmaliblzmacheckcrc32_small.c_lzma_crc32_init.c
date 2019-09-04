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

/* Variables and functions */
 int /*<<< orphan*/  crc32_init ; 
 int /*<<< orphan*/  mythread_once (int /*<<< orphan*/ ) ; 

extern void
lzma_crc32_init(void)
{
	mythread_once(crc32_init);
	return;
}