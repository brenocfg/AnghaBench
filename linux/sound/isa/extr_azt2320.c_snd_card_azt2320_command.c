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
 int EBUSY ; 
 int HZ ; 
 int inb (unsigned long) ; 
 int jiffies ; 
 int /*<<< orphan*/  outb (unsigned char,unsigned long) ; 
 scalar_t__ time_after (unsigned long,int) ; 

__attribute__((used)) static int snd_card_azt2320_command(unsigned long port, unsigned char val)
{
	int i;
	unsigned long limit;

	limit = jiffies + HZ / 10;
	for (i = 50000; i && time_after(limit, jiffies); i--)
		if (!(inb(port + 0x0c) & 0x80)) {
			outb(val, port + 0x0c);
			return 0;
		}
	return -EBUSY;
}