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
typedef  int u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_HMETFR ; 
 int _FALSE ; 
 int _TRUE ; 
 int rtw_read8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 _is_fw_read_cmd_down(_adapter* padapter, u8 msgbox_num)
{
	u8	read_down = _FALSE;
	int 	retry_cnts = 100;
	
	u8 valid;

//	DBG_8192C(" _is_fw_read_cmd_down ,isnormal_chip(%x),reg_1cc(%x),msg_box(%d)...\n",isvern,rtw_read8(padapter,REG_HMETFR),msgbox_num);
	
	do{
		valid = rtw_read8(padapter,REG_HMETFR) & BIT(msgbox_num);
		if(0 == valid ){
			read_down = _TRUE;
		}			
	}while( (!read_down) && (retry_cnts--));

	return read_down;
	
}