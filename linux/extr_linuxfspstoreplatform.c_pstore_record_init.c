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
struct pstore_record {int /*<<< orphan*/  time; struct pstore_info* psi; } ;
struct pstore_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_real_fast_ns () ; 
 int /*<<< orphan*/  memset (struct pstore_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_timespec64 (int /*<<< orphan*/ ) ; 

void pstore_record_init(struct pstore_record *record,
			struct pstore_info *psinfo)
{
	memset(record, 0, sizeof(*record));

	record->psi = psinfo;

	/* Report zeroed timestamp if called before timekeeping has resumed. */
	record->time = ns_to_timespec64(ktime_get_real_fast_ns());
}