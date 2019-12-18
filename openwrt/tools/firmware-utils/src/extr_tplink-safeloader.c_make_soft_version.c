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
typedef  int uint32_t ;
typedef  scalar_t__ time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; } ;
struct soft_version {int pad1; int pad2; void* rev; void* day; void* month; void* year_lo; void* year_hi; scalar_t__ version_patch; scalar_t__ version_minor; scalar_t__ version_major; scalar_t__ zero; void* magic; } ;
struct image_partition_entry {scalar_t__ data; } ;

/* Variables and functions */
 struct image_partition_entry alloc_image_partition (char*,int) ; 
 void* bcd (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 void* htonl (int) ; 
 struct tm* localtime (scalar_t__*) ; 
 int source_date_epoch ; 
 scalar_t__ time (scalar_t__*) ; 

__attribute__((used)) static struct image_partition_entry make_soft_version(uint32_t rev) {
	struct image_partition_entry entry = alloc_image_partition("soft-version", sizeof(struct soft_version));
	struct soft_version *s = (struct soft_version *)entry.data;

	time_t t;

	if (source_date_epoch != -1)
		t = source_date_epoch;
	else if (time(&t) == (time_t)(-1))
		error(1, errno, "time");

	struct tm *tm = localtime(&t);

	s->magic = htonl(0x0000000c);
	s->zero = 0;
	s->pad1 = 0xff;

	s->version_major = 0;
	s->version_minor = 0;
	s->version_patch = 0;

	s->year_hi = bcd((1900+tm->tm_year)/100);
	s->year_lo = bcd(tm->tm_year%100);
	s->month = bcd(tm->tm_mon+1);
	s->day = bcd(tm->tm_mday);
	s->rev = htonl(rev);

	s->pad2 = 0xff;

	return entry;
}