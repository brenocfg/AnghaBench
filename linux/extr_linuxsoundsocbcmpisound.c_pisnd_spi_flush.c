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
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pisnd_spi_start () ; 
 int /*<<< orphan*/  pisnd_workqueue ; 
 int /*<<< orphan*/  spi_fifo_out ; 

__attribute__((used)) static void pisnd_spi_flush(void)
{
	while (!kfifo_is_empty(&spi_fifo_out)) {
		pisnd_spi_start();
		flush_workqueue(pisnd_workqueue);
	}
}