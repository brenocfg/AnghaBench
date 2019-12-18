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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/ * STREAM ;

/* Variables and functions */
 int MCS_DPUM ; 
 int MCS_SDIN ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  in_uint16_be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * iso_recv (int*) ; 

STREAM
mcs_recv(uint16 * channel, uint8 * rdpver)
{
	uint8 opcode, appid, length;
	STREAM s;

	s = iso_recv(rdpver);
	if (s == NULL)
		return NULL;
	if (rdpver != NULL)
		if (*rdpver != 3)
			return s;
	in_uint8(s, opcode);
	appid = opcode >> 2;
	if (appid != MCS_SDIN)
	{
		if (appid != MCS_DPUM)
		{
			error("expected data, got %d\n", opcode);
		}
		return NULL;
	}
	in_uint8s(s, 2);	/* userid */
	in_uint16_be(s, *channel);
	in_uint8s(s, 1);	/* flags */
	in_uint8(s, length);
	if (length & 0x80)
		in_uint8s(s, 1);	/* second byte of length */
	return s;
}