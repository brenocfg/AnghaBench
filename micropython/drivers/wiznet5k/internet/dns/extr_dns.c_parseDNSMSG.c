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
typedef  int uint16_t ;
struct dhdr {int qr; int opcode; int aa; int tc; int rd; int ra; int rcode; int qdcount; int ancount; int nscount; int arcount; void* id; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dns_answer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dns_question (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* get16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dhdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int8_t parseDNSMSG(struct dhdr * pdhdr, uint8_t * pbuf, uint8_t * ip_from_dns)
{
	uint16_t tmp;
	uint16_t i;
	uint8_t * msg;
	uint8_t * cp;

	msg = pbuf;
	memset(pdhdr, 0, sizeof(*pdhdr));

	pdhdr->id = get16(&msg[0]);
	tmp = get16(&msg[2]);
	if (tmp & 0x8000) pdhdr->qr = 1;

	pdhdr->opcode = (tmp >> 11) & 0xf;

	if (tmp & 0x0400) pdhdr->aa = 1;
	if (tmp & 0x0200) pdhdr->tc = 1;
	if (tmp & 0x0100) pdhdr->rd = 1;
	if (tmp & 0x0080) pdhdr->ra = 1;

	pdhdr->rcode = tmp & 0xf;
	pdhdr->qdcount = get16(&msg[4]);
	pdhdr->ancount = get16(&msg[6]);
	pdhdr->nscount = get16(&msg[8]);
	pdhdr->arcount = get16(&msg[10]);


	/* Now parse the variable length sections */
	cp = &msg[12];

	/* Question section */
	for (i = 0; i < pdhdr->qdcount; i++)
	{
		cp = dns_question(msg, cp);
		if(!cp)
		{
#ifdef _DNS_DEBUG_
			printf("MAX_DOMAIN_NAME is too small, it should be redefined in dns.h\r\n");
#endif
			return -1;
		}
	}

	/* Answer section */
	for (i = 0; i < pdhdr->ancount; i++)
	{
		cp = dns_answer(msg, cp, ip_from_dns);
		if(!cp)
		{
#ifdef _DNS_DEBUG_
			printf("MAX_DOMAIN_NAME is too small, it should be redefined in dns.h\r\n");
#endif
			return -1;
		}

	}

	/* Name server (authority) section */
	for (i = 0; i < pdhdr->nscount; i++)
	{
		;
	}

	/* Additional section */
	for (i = 0; i < pdhdr->arcount; i++)
	{
		;
	}

	if(pdhdr->rcode == 0) return 1;		// No error
	else return 0;
}