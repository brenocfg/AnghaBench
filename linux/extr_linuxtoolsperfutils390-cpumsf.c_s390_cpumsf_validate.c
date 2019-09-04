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
struct hws_trailer_entry {unsigned short bsdes; unsigned short dsdes; } ;
struct hws_basic_entry {int def; } ;

/* Variables and functions */
 int S390_CPUMSF_PAGESZ ; 

__attribute__((used)) static bool s390_cpumsf_validate(int machine_type,
				 unsigned char *buf, size_t len,
				 unsigned short *bsdes,
				 unsigned short *dsdes)
{
	struct hws_basic_entry *basic = (struct hws_basic_entry *)buf;
	struct hws_trailer_entry *te;

	*dsdes = *bsdes = 0;
	if (len & (S390_CPUMSF_PAGESZ - 1))	/* Illegal size */
		return false;
	if (basic->def != 1)		/* No basic set entry, must be first */
		return false;
	/* Check for trailer entry at end of SDB */
	te = (struct hws_trailer_entry *)(buf + S390_CPUMSF_PAGESZ
					      - sizeof(*te));
	*bsdes = te->bsdes;
	*dsdes = te->dsdes;
	if (!te->bsdes && !te->dsdes) {
		/* Very old hardware, use CPUID */
		switch (machine_type) {
		case 2097:
		case 2098:
			*dsdes = 64;
			*bsdes = 32;
			break;
		case 2817:
		case 2818:
			*dsdes = 74;
			*bsdes = 32;
			break;
		case 2827:
		case 2828:
			*dsdes = 85;
			*bsdes = 32;
			break;
		case 2964:
		case 2965:
			*dsdes = 112;
			*bsdes = 32;
			break;
		default:
			/* Illegal trailer entry */
			return false;
		}
	}
	return true;
}