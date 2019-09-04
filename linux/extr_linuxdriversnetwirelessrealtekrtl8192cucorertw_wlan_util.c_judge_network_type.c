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
struct mlme_ext_info {scalar_t__ HT_enable; } ;
struct mlme_ext_priv {int cur_channel; struct mlme_ext_info mlmext_info; } ;
struct TYPE_3__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int WIRELESS_11A ; 
 int WIRELESS_11B ; 
 int WIRELESS_11BG ; 
 int WIRELESS_11G ; 
 int WIRELESS_11_24N ; 
 int WIRELESS_11_5N ; 
 scalar_t__ _TRUE ; 
 scalar_t__ cckrates_included (unsigned char*,int) ; 
 scalar_t__ cckratesonly_included (unsigned char*,int) ; 

int judge_network_type(_adapter *padapter, unsigned char *rate, int ratelen)
{
	int network_type = 0;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	

	if(pmlmeext->cur_channel > 14)
	{
		if (pmlmeinfo->HT_enable)
		{
			network_type = WIRELESS_11_5N;
		}
	
		network_type |= WIRELESS_11A;
	}
	else
	{
		if (pmlmeinfo->HT_enable)
		{
			network_type = WIRELESS_11_24N;
		}

		if ((cckratesonly_included(rate, ratelen)) == _TRUE)
		{
			network_type |= WIRELESS_11B;
		}
		else if((cckrates_included(rate, ratelen)) == _TRUE)
		{
			network_type |= WIRELESS_11BG;
		}
		else
		{
			network_type |= WIRELESS_11G;
		}
	}
		
	return 	network_type;
}