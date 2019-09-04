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

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IO_REG ; 
 int /*<<< orphan*/  AUX_MU_LSR_REG ; 
 int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,char) ; 

void mini_uart_send ( char c )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x20) 
			break;
	}
	put32(AUX_MU_IO_REG,c);
}