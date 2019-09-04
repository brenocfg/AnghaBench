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
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

u8 *rtw_get_ie(u8 *pbuf, sint index, sint *len, sint limit)
{
	sint tmp,i;
	u8 *p;
_func_enter_;
	if (limit < 1){
		_func_exit_;	
		return NULL;
	}

	p = pbuf;
	i = 0;
	*len = 0;
	while(1)
	{
		if (*p == index)
		{
			*len = *(p + 1);
			return (p);
		}
		else
		{
			tmp = *(p + 1);
			p += (tmp + 2);
			i += (tmp + 2);
		}
		if (i >= limit)
			break;
	}
_func_exit_;		
	return NULL;
}