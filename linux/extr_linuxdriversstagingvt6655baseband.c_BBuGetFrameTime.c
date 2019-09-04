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
 unsigned char PK_TYPE_11A ; 
 unsigned int RATE_54M ; 
 scalar_t__* awcFrameTime ; 

unsigned int
BBuGetFrameTime(
	unsigned char byPreambleType,
	unsigned char byPktType,
	unsigned int cbFrameLength,
	unsigned short wRate
)
{
	unsigned int uFrameTime;
	unsigned int uPreamble;
	unsigned int uTmp;
	unsigned int uRateIdx = (unsigned int)wRate;
	unsigned int uRate = 0;

	if (uRateIdx > RATE_54M)
		return 0;

	uRate = (unsigned int)awcFrameTime[uRateIdx];

	if (uRateIdx <= 3) {          /* CCK mode */
		if (byPreambleType == 1) /* Short */
			uPreamble = 96;
		else
			uPreamble = 192;

		uFrameTime = (cbFrameLength * 80) / uRate;  /* ????? */
		uTmp = (uFrameTime * uRate) / 80;
		if (cbFrameLength != uTmp)
			uFrameTime++;

		return uPreamble + uFrameTime;
	}
	uFrameTime = (cbFrameLength * 8 + 22) / uRate; /* ???????? */
	uTmp = ((uFrameTime * uRate) - 22) / 8;
	if (cbFrameLength != uTmp)
		uFrameTime++;

	uFrameTime = uFrameTime * 4;    /* ??????? */
	if (byPktType != PK_TYPE_11A)
		uFrameTime += 6;     /* ?????? */

	return 20 + uFrameTime; /* ?????? */
}