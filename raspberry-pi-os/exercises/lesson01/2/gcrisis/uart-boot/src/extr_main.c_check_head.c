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
typedef  size_t uint8_t ;

/* Variables and functions */
 char uart_recv () ; 
 int /*<<< orphan*/  uart_send_string (char*) ; 

void check_head(char *h,int hlen)
{
    uint8_t index=0;
    while(1)
	{
		char c=uart_recv();
		if(c==h[index])
		{
			index++;
		}
		else
		{
			if(c==h[0])
				index=1;
			else
				index=0;
		}
		if(index==hlen)
			break;
	}
	uart_send_string("OK");
}