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
typedef  unsigned int uint ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */

int rtw_restruct_wmm_ie(_adapter *adapter, u8 *in_ie, u8 *out_ie, uint in_len, uint initial_out_len)
{
	unsigned	int ielength=0;
	unsigned int i, j;

	i = 12; //after the fixed IE
	while(i<in_len)
	{
		ielength = initial_out_len;		
		
		if(in_ie[i] == 0xDD && in_ie[i+2] == 0x00 && in_ie[i+3] == 0x50  && in_ie[i+4] == 0xF2 && in_ie[i+5] == 0x02 && i+5 < in_len) //WMM element ID and OUI
		{

			//Append WMM IE to the last index of out_ie
			/*
			for(j=i; j< i+(in_ie[i+1]+2); j++)
			{
				out_ie[ielength] = in_ie[j];				
				ielength++;
			}
			out_ie[initial_out_len+8] = 0x00; //force the QoS Info Field to be zero
	                */
                       
                        for ( j = i; j < i + 9; j++ )
                        {
                            out_ie[ ielength] = in_ie[ j ];
                            ielength++;
                        } 
                        out_ie[ initial_out_len + 1 ] = 0x07;
                        out_ie[ initial_out_len + 6 ] = 0x00;
                        out_ie[ initial_out_len + 8 ] = 0x00;
	
			break;
		}

		i+=(in_ie[i+1]+2); // to the next IE element
	}
	
	return ielength;
	
}