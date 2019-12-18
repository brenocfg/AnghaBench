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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_MSGID ; 
 int /*<<< orphan*/  DNS_MSG_ID ; 
 int /*<<< orphan*/  DNS_SOCKET ; 
 int /*<<< orphan*/ * pDNSMSG ; 

void DNS_init(uint8_t s, uint8_t * buf)
{
	DNS_SOCKET = s; // SOCK_DNS
	pDNSMSG = buf; // User's shared buffer
	DNS_MSGID = DNS_MSG_ID;
}