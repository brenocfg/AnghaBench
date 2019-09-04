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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;
struct goldfish_tty {int /*<<< orphan*/  irq; int /*<<< orphan*/ * base; TYPE_1__ console; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct platform_device*) ; 
 scalar_t__ goldfish_tty_current_line_count ; 
 int /*<<< orphan*/  goldfish_tty_delete_driver () ; 
 int /*<<< orphan*/  goldfish_tty_driver ; 
 int /*<<< orphan*/  goldfish_tty_lock ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct goldfish_tty* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_console (TYPE_1__*) ; 

__attribute__((used)) static int goldfish_tty_remove(struct platform_device *pdev)
{
	struct goldfish_tty *qtty = platform_get_drvdata(pdev);

	mutex_lock(&goldfish_tty_lock);

	unregister_console(&qtty->console);
	tty_unregister_device(goldfish_tty_driver, qtty->console.index);
	iounmap(qtty->base);
	qtty->base = NULL;
	free_irq(qtty->irq, pdev);
	goldfish_tty_current_line_count--;
	if (goldfish_tty_current_line_count == 0)
		goldfish_tty_delete_driver();
	mutex_unlock(&goldfish_tty_lock);
	return 0;
}