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
struct file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EFAULT ; 
 int /*<<< orphan*/  WDT_FLAGS_EXPECT_CLOSE ; 
 int /*<<< orphan*/  ath79_wdt_keepalive () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ get_user (char,char const*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_flags ; 

__attribute__((used)) static ssize_t ath79_wdt_write(struct file *file, const char *data,
				size_t len, loff_t *ppos)
{
	if (len) {
		if (!nowayout) {
			size_t i;

			clear_bit(WDT_FLAGS_EXPECT_CLOSE, &wdt_flags);

			for (i = 0; i != len; i++) {
				char c;

				if (get_user(c, data + i))
					return -EFAULT;

				if (c == 'V')
					set_bit(WDT_FLAGS_EXPECT_CLOSE,
						&wdt_flags);
			}
		}

		ath79_wdt_keepalive();
	}

	return len;
}