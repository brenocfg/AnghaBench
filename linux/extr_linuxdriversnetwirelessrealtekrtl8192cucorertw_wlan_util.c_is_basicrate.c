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
struct mlme_ext_priv {unsigned char* basicrate; } ;
struct TYPE_3__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int NumRates ; 
 int _FALSE ; 
 int _TRUE ; 
 unsigned char ratetbl_val_2wifirate (unsigned char) ; 

int is_basicrate(_adapter *padapter, unsigned char rate)
{
	int i;
	unsigned char val;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	
	for(i = 0; i < NumRates; i++)
	{
		val = pmlmeext->basicrate[i];

		if ((val != 0xff) && (val != 0xfe))
		{
			if (rate == ratetbl_val_2wifirate(val))
			{
				return _TRUE;
			}
		}
	}
	
	return _FALSE;
}