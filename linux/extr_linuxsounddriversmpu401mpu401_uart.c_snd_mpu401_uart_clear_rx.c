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
struct snd_mpu401 {int /*<<< orphan*/  (* read ) (struct snd_mpu401*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPU401D (struct snd_mpu401*) ; 
 scalar_t__ snd_mpu401_input_avail (struct snd_mpu401*) ; 
 int /*<<< orphan*/  stub1 (struct snd_mpu401*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_mpu401_uart_clear_rx(struct snd_mpu401 *mpu)
{
	int timeout = 100000;
	for (; timeout > 0 && snd_mpu401_input_avail(mpu); timeout--)
		mpu->read(mpu, MPU401D(mpu));
#ifdef CONFIG_SND_DEBUG
	if (timeout <= 0)
		snd_printk(KERN_ERR "cmd: clear rx timeout (status = 0x%x)\n",
			   mpu->read(mpu, MPU401C(mpu)));
#endif
}