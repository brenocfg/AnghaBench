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
struct es2_ap_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APB1_LOG_MSG_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  apb_log_get (struct es2_ap_dev*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int apb_log_poll(void *data)
{
	struct es2_ap_dev *es2 = data;
	char *buf;

	buf = kmalloc(APB1_LOG_MSG_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	while (!kthread_should_stop()) {
		msleep(1000);
		apb_log_get(es2, buf);
	}

	kfree(buf);

	return 0;
}