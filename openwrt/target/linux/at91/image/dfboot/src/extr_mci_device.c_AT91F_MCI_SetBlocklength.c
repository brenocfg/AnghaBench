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
typedef  int /*<<< orphan*/  AT91PS_MciDevice ;

/* Variables and functions */
 int /*<<< orphan*/  AT91C_SET_BLOCKLEN_CMD ; 
 int AT91F_MCI_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int AT91F_MCI_SetBlocklength(AT91PS_MciDevice pMCI_Device,unsigned int length)
{
    return( AT91F_MCI_SendCommand(pMCI_Device, AT91C_SET_BLOCKLEN_CMD, length) );
}