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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_printk (char*,int,int,int,int) ; 

__attribute__((used)) static void mvs_set_sense(u8 *buffer, int len, int d_sense,
		int key, int asc, int ascq)
{
	memset(buffer, 0, len);

	if (d_sense) {
		/* Descriptor format */
		if (len < 4) {
			mv_printk("Length %d of sense buffer too small to "
				"fit sense %x:%x:%x", len, key, asc, ascq);
		}

		buffer[0] = 0x72;		/* Response Code	*/
		if (len > 1)
			buffer[1] = key;	/* Sense Key */
		if (len > 2)
			buffer[2] = asc;	/* ASC	*/
		if (len > 3)
			buffer[3] = ascq;	/* ASCQ	*/
	} else {
		if (len < 14) {
			mv_printk("Length %d of sense buffer too small to "
				"fit sense %x:%x:%x", len, key, asc, ascq);
		}

		buffer[0] = 0x70;		/* Response Code	*/
		if (len > 2)
			buffer[2] = key;	/* Sense Key */
		if (len > 7)
			buffer[7] = 0x0a;	/* Additional Sense Length */
		if (len > 12)
			buffer[12] = asc;	/* ASC */
		if (len > 13)
			buffer[13] = ascq; /* ASCQ */
	}

	return;
}