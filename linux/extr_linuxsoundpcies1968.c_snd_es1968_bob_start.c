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
struct es1968 {int bob_freq; } ;

/* Variables and functions */
 int ESS_SYSCLK ; 
 int __maestro_read (struct es1968*,int) ; 
 int /*<<< orphan*/  __maestro_write (struct es1968*,int,int) ; 

__attribute__((used)) static void snd_es1968_bob_start(struct es1968 *chip)
{
	int prescale;
	int divide;

	/* compute ideal interrupt frequency for buffer size & play rate */
	/* first, find best prescaler value to match freq */
	for (prescale = 5; prescale < 12; prescale++)
		if (chip->bob_freq > (ESS_SYSCLK >> (prescale + 9)))
			break;

	/* next, back off prescaler whilst getting divider into optimum range */
	divide = 1;
	while ((prescale > 5) && (divide < 32)) {
		prescale--;
		divide <<= 1;
	}
	divide >>= 1;

	/* now fine-tune the divider for best match */
	for (; divide < 31; divide++)
		if (chip->bob_freq >
		    ((ESS_SYSCLK >> (prescale + 9)) / (divide + 1))) break;

	/* divide = 0 is illegal, but don't let prescale = 4! */
	if (divide == 0) {
		divide++;
		if (prescale > 5)
			prescale--;
	} else if (divide > 1)
		divide--;

	__maestro_write(chip, 6, 0x9000 | (prescale << 5) | divide);	/* set reg */

	/* Now set IDR 11/17 */
	__maestro_write(chip, 0x11, __maestro_read(chip, 0x11) | 1);
	__maestro_write(chip, 0x17, __maestro_read(chip, 0x17) | 1);
}