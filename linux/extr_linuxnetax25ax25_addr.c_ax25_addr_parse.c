#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lastrepeat; int ndigi; int* repeated; int /*<<< orphan*/ * calls; } ;
typedef  TYPE_1__ ax25_digi ;
typedef  int /*<<< orphan*/  ax25_address ;

/* Variables and functions */
 int AX25_ADDR_LEN ; 
 unsigned char const AX25_CBIT ; 
 int AX25_COMMAND ; 
 unsigned char const AX25_DAMA_FLAG ; 
 unsigned char const AX25_EBIT ; 
 unsigned char const AX25_HBIT ; 
 int AX25_MAX_DIGIS ; 
 int AX25_RESPONSE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 

const unsigned char *ax25_addr_parse(const unsigned char *buf, int len,
	ax25_address *src, ax25_address *dest, ax25_digi *digi, int *flags,
	int *dama)
{
	int d = 0;

	if (len < 14) return NULL;

	if (flags != NULL) {
		*flags = 0;

		if (buf[6] & AX25_CBIT)
			*flags = AX25_COMMAND;
		if (buf[13] & AX25_CBIT)
			*flags = AX25_RESPONSE;
	}

	if (dama != NULL)
		*dama = ~buf[13] & AX25_DAMA_FLAG;

	/* Copy to, from */
	if (dest != NULL)
		memcpy(dest, buf + 0, AX25_ADDR_LEN);
	if (src != NULL)
		memcpy(src,  buf + 7, AX25_ADDR_LEN);

	buf += 2 * AX25_ADDR_LEN;
	len -= 2 * AX25_ADDR_LEN;

	digi->lastrepeat = -1;
	digi->ndigi      = 0;

	while (!(buf[-1] & AX25_EBIT)) {
		if (d >= AX25_MAX_DIGIS)
			return NULL;
		if (len < AX25_ADDR_LEN)
			return NULL;

		memcpy(&digi->calls[d], buf, AX25_ADDR_LEN);
		digi->ndigi = d + 1;

		if (buf[6] & AX25_HBIT) {
			digi->repeated[d] = 1;
			digi->lastrepeat  = d;
		} else {
			digi->repeated[d] = 0;
		}

		buf += AX25_ADDR_LEN;
		len -= AX25_ADDR_LEN;
		d++;
	}

	return buf;
}