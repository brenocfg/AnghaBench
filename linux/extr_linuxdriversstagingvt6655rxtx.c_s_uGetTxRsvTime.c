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
struct vnt_private {unsigned int uSIFS; scalar_t__ byTopOFDMBasicRate; int /*<<< orphan*/  byPreambleType; scalar_t__ byTopCCKBasicRate; } ;

/* Variables and functions */
 unsigned int BBuGetFrameTime (int /*<<< orphan*/ ,unsigned char,int,unsigned short) ; 
 unsigned char PK_TYPE_11B ; 

__attribute__((used)) static
unsigned int
s_uGetTxRsvTime(
	struct vnt_private *pDevice,
	unsigned char byPktType,
	unsigned int cbFrameLength,
	unsigned short wRate,
	bool bNeedAck
)
{
	unsigned int uDataTime, uAckTime;

	uDataTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, cbFrameLength, wRate);
	if (byPktType == PK_TYPE_11B) /* llb,CCK mode */
		uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, (unsigned short)pDevice->byTopCCKBasicRate);
	else /* 11g 2.4G OFDM mode & 11a 5G OFDM mode */
		uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, (unsigned short)pDevice->byTopOFDMBasicRate);

	if (bNeedAck)
		return uDataTime + pDevice->uSIFS + uAckTime;
	else
		return uDataTime;
}