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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t *get_next_inst_ip(uint8_t *addr)
{
	uint8_t *ip = addr;
	uint8_t sib;
	uint8_t rm;
	uint8_t mod;
	uint8_t base;
	uint8_t modrm;

	/* determine the prefix. */
	switch(*ip) {
	case 0xf2:
	case 0xf3:
	case 0x66:
		ip++;
		break;
	}

	/* look for rex prefix */
	if ((*ip & 0x40) == 0x40)
		ip++;

	/* Make sure we have a MPX instruction. */
	if (*ip++ != 0x0f)
		return addr;

	/* Skip the op code byte. */
	ip++;

	/* Get the modrm byte. */
	modrm = *ip++;

	/* Break it down into parts. */
	rm = modrm & 7;
	mod = (modrm >> 6);

	/* Init the parts of the address mode. */
	base = 8;

	/* Is it a mem mode? */
	if (mod != 3) {
		/* look for scaled indexed addressing */
		if (rm == 4) {
			/* SIB addressing */
			sib = *ip++;
			base = sib & 7;
			switch (mod) {
			case 0:
				if (base == 5)
					ip += 4;
				break;

			case 1:
				ip++;
				break;

			case 2:
				ip += 4;
				break;
			}

		} else {
			/* MODRM addressing */
			switch (mod) {
			case 0:
				/* DISP32 addressing, no base */
				if (rm == 5)
					ip += 4;
				break;

			case 1:
				ip++;
				break;

			case 2:
				ip += 4;
				break;
			}
		}
	}
	return ip;
}