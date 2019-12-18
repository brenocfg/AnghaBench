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
 int MAXCNAME ; 
#define  TYPE_A 138 
#define  TYPE_CNAME 137 
#define  TYPE_HINFO 136 
#define  TYPE_MB 135 
#define  TYPE_MG 134 
#define  TYPE_MR 133 
#define  TYPE_MX 132 
#define  TYPE_NS 131 
#define  TYPE_PTR 130 
#define  TYPE_SOA 129 
#define  TYPE_TXT 128 
 int get16 (int /*<<< orphan*/ *) ; 
 int parse_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

uint8_t * dns_answer(uint8_t * msg, uint8_t * cp, uint8_t * ip_from_dns)
{
	int len, type;
	char name[MAXCNAME];

	len = parse_name(msg, cp, name, MAXCNAME);

	if (len == -1) return 0;

	cp += len;
	type = get16(cp);
	cp += 2;		/* type */
	cp += 2;		/* class */
	cp += 4;		/* ttl */
	cp += 2;		/* len */


	switch (type)
	{
	case TYPE_A:
		/* Just read the address directly into the structure */
		ip_from_dns[0] = *cp++;
		ip_from_dns[1] = *cp++;
		ip_from_dns[2] = *cp++;
		ip_from_dns[3] = *cp++;
		break;
	case TYPE_CNAME:
	case TYPE_MB:
	case TYPE_MG:
	case TYPE_MR:
	case TYPE_NS:
	case TYPE_PTR:
		/* These types all consist of a single domain name */
		/* convert it to ASCII format */
		len = parse_name(msg, cp, name, MAXCNAME);
		if (len == -1) return 0;

		cp += len;
		break;
	case TYPE_HINFO:
		len = *cp++;
		cp += len;

		len = *cp++;
		cp += len;
		break;
	case TYPE_MX:
		cp += 2;
		/* Get domain name of exchanger */
		len = parse_name(msg, cp, name, MAXCNAME);
		if (len == -1) return 0;

		cp += len;
		break;
	case TYPE_SOA:
		/* Get domain name of name server */
		len = parse_name(msg, cp, name, MAXCNAME);
		if (len == -1) return 0;

		cp += len;

		/* Get domain name of responsible person */
		len = parse_name(msg, cp, name, MAXCNAME);
		if (len == -1) return 0;

		cp += len;

		cp += 4;
		cp += 4;
		cp += 4;
		cp += 4;
		cp += 4;
		break;
	case TYPE_TXT:
		/* Just stash */
		break;
	default:
		/* Ignore */
		break;
	}

	return cp;
}