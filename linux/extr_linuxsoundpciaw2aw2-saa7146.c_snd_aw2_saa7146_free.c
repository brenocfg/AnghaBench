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
struct snd_aw2_saa7146 {int /*<<< orphan*/ * base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  MC1 ; 
 int MRST_N ; 
 int /*<<< orphan*/  WRITEREG (int,int /*<<< orphan*/ ) ; 

int snd_aw2_saa7146_free(struct snd_aw2_saa7146 *chip)
{
	/* disable all irqs */
	WRITEREG(0, IER);

	/* reset saa7146 */
	WRITEREG((MRST_N << 16), MC1);

	/* Unset base addr */
	chip->base_addr = NULL;

	return 0;
}