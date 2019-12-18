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
typedef  int u32 ;
struct rate_info {int mcs; int bw; int nss; int flags; } ;

/* Variables and functions */
#define  RATE_INFO_BW_10 133 
#define  RATE_INFO_BW_160 132 
#define  RATE_INFO_BW_20 131 
#define  RATE_INFO_BW_40 130 
#define  RATE_INFO_BW_5 129 
#define  RATE_INFO_BW_80 128 
 int RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,size_t,int) ; 

__attribute__((used)) static u32 cfg80211_calculate_bitrate_vht(struct rate_info *rate)
{
	static const u32 base[4][10] = {
		{   6500000,
		   13000000,
		   19500000,
		   26000000,
		   39000000,
		   52000000,
		   58500000,
		   65000000,
		   78000000,
		/* not in the spec, but some devices use this: */
		   86500000,
		},
		{  13500000,
		   27000000,
		   40500000,
		   54000000,
		   81000000,
		  108000000,
		  121500000,
		  135000000,
		  162000000,
		  180000000,
		},
		{  29300000,
		   58500000,
		   87800000,
		  117000000,
		  175500000,
		  234000000,
		  263300000,
		  292500000,
		  351000000,
		  390000000,
		},
		{  58500000,
		  117000000,
		  175500000,
		  234000000,
		  351000000,
		  468000000,
		  526500000,
		  585000000,
		  702000000,
		  780000000,
		},
	};
	u32 bitrate;
	int idx;

	if (rate->mcs > 9)
		goto warn;

	switch (rate->bw) {
	case RATE_INFO_BW_160:
		idx = 3;
		break;
	case RATE_INFO_BW_80:
		idx = 2;
		break;
	case RATE_INFO_BW_40:
		idx = 1;
		break;
	case RATE_INFO_BW_5:
	case RATE_INFO_BW_10:
	default:
		goto warn;
	case RATE_INFO_BW_20:
		idx = 0;
	}

	bitrate = base[idx][rate->mcs];
	bitrate *= rate->nss;

	if (rate->flags & RATE_INFO_FLAGS_SHORT_GI)
		bitrate = (bitrate / 9) * 10;

	/* do NOT round down here */
	return (bitrate + 50000) / 100000;
 warn:
	WARN_ONCE(1, "invalid rate bw=%d, mcs=%d, nss=%d\n",
		  rate->bw, rate->mcs, rate->nss);
	return 0;
}