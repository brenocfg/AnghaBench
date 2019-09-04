#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_priv {unsigned char* datarate; } ;
struct TYPE_4__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 unsigned char IEEE80211_BASIC_RATE_MASK ; 
 int NumRates ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  is_basicrate (TYPE_1__*,unsigned char) ; 
 unsigned char ratetbl_val_2wifirate (unsigned char) ; 

unsigned int ratetbl2rateset(_adapter *padapter, unsigned char *rateset)
{
	int i;
	unsigned char rate;
	unsigned int	len = 0;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	for (i = 0; i < NumRates; i++)
	{
		rate = pmlmeext->datarate[i];

		switch (rate)
		{
			case 0xff:
				return len;
				
			case 0xfe:
				continue;
				
			default:
				rate = ratetbl_val_2wifirate(rate);

				if (is_basicrate(padapter, rate) == _TRUE)
				{
					rate |= IEEE80211_BASIC_RATE_MASK;
				}
				
				rateset[len] = rate;
				len++;
				break;
		}
	}
	return len;
}