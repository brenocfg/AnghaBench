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
struct TYPE_3__ {int /*<<< orphan*/  UUIE; int /*<<< orphan*/  MessageType; } ;
typedef  TYPE_1__ Q931 ;

/* Variables and functions */
 int DecodeH323_UserInformation (unsigned char*,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int H323_ERROR_BOUND ; 
 int H323_ERROR_RANGE ; 
 int /*<<< orphan*/  PRINT (char*,...) ; 

int DecodeQ931(unsigned char *buf, size_t sz, Q931 *q931)
{
	unsigned char *p = buf;
	int len;

	if (!p || sz < 1)
		return H323_ERROR_BOUND;

	/* Protocol Discriminator */
	if (*p != 0x08) {
		PRINT("Unknown Protocol Discriminator\n");
		return H323_ERROR_RANGE;
	}
	p++;
	sz--;

	/* CallReferenceValue */
	if (sz < 1)
		return H323_ERROR_BOUND;
	len = *p++;
	sz--;
	if (sz < len)
		return H323_ERROR_BOUND;
	p += len;
	sz -= len;

	/* Message Type */
	if (sz < 2)
		return H323_ERROR_BOUND;
	q931->MessageType = *p++;
	sz--;
	PRINT("MessageType = %02X\n", q931->MessageType);
	if (*p & 0x80) {
		p++;
		sz--;
	}

	/* Decode Information Elements */
	while (sz > 0) {
		if (*p == 0x7e) {	/* UserUserIE */
			if (sz < 3)
				break;
			p++;
			len = *p++ << 8;
			len |= *p++;
			sz -= 3;
			if (sz < len)
				break;
			p++;
			len--;
			return DecodeH323_UserInformation(buf, p, len,
							  &q931->UUIE);
		}
		p++;
		sz--;
		if (sz < 1)
			break;
		len = *p++;
		sz--;
		if (sz < len)
			break;
		p += len;
		sz -= len;
	}

	PRINT("Q.931 UUIE not found\n");

	return H323_ERROR_BOUND;
}