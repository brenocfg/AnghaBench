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
struct esp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FFLAGS ; 
 unsigned int ESP_FF_FBYTES ; 
 int /*<<< orphan*/  ESP_STATUS ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned int zorro_esp_read8 (struct esp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int zorro_esp_wait_for_fifo(struct esp *esp)
{
	int i = 500000;

	do {
		unsigned int fbytes = zorro_esp_read8(esp, ESP_FFLAGS)
							& ESP_FF_FBYTES;

		if (fbytes)
			return fbytes;

		udelay(2);
	} while (--i);

	pr_err("FIFO is empty (sreg %02x)\n",
	       zorro_esp_read8(esp, ESP_STATUS));
	return 0;
}