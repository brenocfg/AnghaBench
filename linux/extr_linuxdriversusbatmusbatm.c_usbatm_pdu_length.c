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
 int ATM_AAL5_TRAILER ; 
 int ATM_CELL_PAYLOAD ; 

__attribute__((used)) static inline unsigned int usbatm_pdu_length(unsigned int length)
{
	length += ATM_CELL_PAYLOAD - 1 + ATM_AAL5_TRAILER;
	return length - length % ATM_CELL_PAYLOAD;
}