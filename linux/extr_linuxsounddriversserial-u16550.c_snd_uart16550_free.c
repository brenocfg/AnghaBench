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
struct snd_uart16550 {scalar_t__ irq; int /*<<< orphan*/  res_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_uart16550*) ; 
 int /*<<< orphan*/  kfree (struct snd_uart16550*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_uart16550_free(struct snd_uart16550 *uart)
{
	if (uart->irq >= 0)
		free_irq(uart->irq, uart);
	release_and_free_resource(uart->res_base);
	kfree(uart);
	return 0;
}