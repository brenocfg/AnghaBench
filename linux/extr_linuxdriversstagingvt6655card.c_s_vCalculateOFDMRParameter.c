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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BB_TYPE_11A ; 
#define  RATE_12M 135 
#define  RATE_18M 134 
#define  RATE_24M 133 
#define  RATE_36M 132 
#define  RATE_48M 131 
#define  RATE_54M 130 
#define  RATE_6M 129 
#define  RATE_9M 128 

__attribute__((used)) static
void
s_vCalculateOFDMRParameter(
	unsigned char byRate,
	u8 bb_type,
	unsigned char *pbyTxRate,
	unsigned char *pbyRsvTime
)
{
	switch (byRate) {
	case RATE_6M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x9B;
			*pbyRsvTime = 44;
		} else {
			*pbyTxRate = 0x8B;
			*pbyRsvTime = 50;
		}
		break;

	case RATE_9M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x9F;
			*pbyRsvTime = 36;
		} else {
			*pbyTxRate = 0x8F;
			*pbyRsvTime = 42;
		}
		break;

	case RATE_12M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x9A;
			*pbyRsvTime = 32;
		} else {
			*pbyTxRate = 0x8A;
			*pbyRsvTime = 38;
		}
		break;

	case RATE_18M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x9E;
			*pbyRsvTime = 28;
		} else {
			*pbyTxRate = 0x8E;
			*pbyRsvTime = 34;
		}
		break;

	case RATE_36M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x9D;
			*pbyRsvTime = 24;
		} else {
			*pbyTxRate = 0x8D;
			*pbyRsvTime = 30;
		}
		break;

	case RATE_48M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x98;
			*pbyRsvTime = 24;
		} else {
			*pbyTxRate = 0x88;
			*pbyRsvTime = 30;
		}
		break;

	case RATE_54M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x9C;
			*pbyRsvTime = 24;
		} else {
			*pbyTxRate = 0x8C;
			*pbyRsvTime = 30;
		}
		break;

	case RATE_24M:
	default:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*pbyTxRate = 0x99;
			*pbyRsvTime = 28;
		} else {
			*pbyTxRate = 0x89;
			*pbyRsvTime = 34;
		}
		break;
	}
}