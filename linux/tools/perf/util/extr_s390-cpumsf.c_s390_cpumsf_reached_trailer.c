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
struct hws_trailer_entry {int dummy; } ;

/* Variables and functions */
 int S390_CPUMSF_PAGESZ ; 

__attribute__((used)) static bool s390_cpumsf_reached_trailer(size_t entry_sz, size_t pos)
{
	size_t payload = S390_CPUMSF_PAGESZ - sizeof(struct hws_trailer_entry);

	if (payload - (pos & (S390_CPUMSF_PAGESZ - 1)) < entry_sz)
		return false;
	return true;
}