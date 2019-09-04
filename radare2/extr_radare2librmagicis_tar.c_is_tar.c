#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_2__ {int* chksum; int /*<<< orphan*/  magic; } ;
union record {char* charptr; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTMAGIC ; 
 int /*<<< orphan*/  TMAGIC ; 
 int from_oct (int,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_tar(const ut8 *buf, size_t nbytes) {
	const union record *header = (const union record *)(const void *)buf;
	int i, sum, recsum;
	const char *p;

	if (nbytes < sizeof (union record)) {
		return 0;
	}

	recsum = from_oct (8, header->header.chksum);

	sum = 0;
	p = header->charptr;
	for (i = sizeof(union record); --i >= 0;) {
		/*
		 * We cannot use ut8 here because of old compilers,
		 * e.g. V7.
		 */
		sum += 0xFF & *p++;
	}

	/* Adjust checksum to count the "chksum" field as blanks. */
	for (i = sizeof header->header.chksum; --i >= 0;) {
		sum -= 0xFF & header->header.chksum[i];
	}
	sum += ' ' * sizeof header->header.chksum;
	if (sum != recsum) {
		return 0; /* Not a tar archive */
	}
	if (strcmp (header->header.magic, GNUTMAGIC) == 0) {
		return 3; /* GNU Unix Standard tar archive */
	}
	if (strcmp (header->header.magic, TMAGIC) == 0) {
		return 2; /* Unix Standard tar archive */
	}
	return 1;			/* Old fashioned tar archive */
}