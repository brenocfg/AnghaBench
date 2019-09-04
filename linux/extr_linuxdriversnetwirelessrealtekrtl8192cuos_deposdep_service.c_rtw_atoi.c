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
typedef  char u8 ;
typedef  int u32 ;

/* Variables and functions */
 int strlen (char*) ; 

u32 rtw_atoi(u8* s)
{

	int num=0,flag=0;
	int i;
	for(i=0;i<=strlen(s);i++)
	{
	  if(s[i] >= '0' && s[i] <= '9')
		 num = num * 10 + s[i] -'0';
	  else if(s[0] == '-' && i==0) 
		 flag =1;
	  else 
		  break;
	 }

	if(flag == 1)
	   num = num * -1;

	 return(num); 

}