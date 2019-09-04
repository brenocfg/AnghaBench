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
struct sockaddr_dn {int /*<<< orphan*/  sdn_objnamel; int /*<<< orphan*/  sdn_objname; int /*<<< orphan*/  sdn_objnum; } ;

/* Variables and functions */
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int dn_sockaddr2username(struct sockaddr_dn *sdn, unsigned char *buf, unsigned char type)
{
	int len = 2;

	*buf++ = type;

	switch (type) {
	case 0:
		*buf++ = sdn->sdn_objnum;
		break;
	case 1:
		*buf++ = 0;
		*buf++ = le16_to_cpu(sdn->sdn_objnamel);
		memcpy(buf, sdn->sdn_objname, le16_to_cpu(sdn->sdn_objnamel));
		len = 3 + le16_to_cpu(sdn->sdn_objnamel);
		break;
	case 2:
		memset(buf, 0, 5);
		buf += 5;
		*buf++ = le16_to_cpu(sdn->sdn_objnamel);
		memcpy(buf, sdn->sdn_objname, le16_to_cpu(sdn->sdn_objnamel));
		len = 7 + le16_to_cpu(sdn->sdn_objnamel);
		break;
	}

	return len;
}