#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int /*<<< orphan*/ * file_name; } ;
typedef  int /*<<< orphan*/  SGUID ;
typedef  TYPE_1__ SCV_RSDS_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int const) ; 
 scalar_t__ strdup (char const*) ; 

__attribute__((used)) static bool get_rsds(ut8* dbg_data, int dbg_data_len, SCV_RSDS_HEADER* res) {
	const int rsds_sz = 4 + sizeof (SGUID) + 4;
	if (dbg_data_len < rsds_sz) {
		return false;
	}
	memcpy (res, dbg_data, rsds_sz);
	res->file_name = (ut8*) strdup ((const char*) dbg_data + rsds_sz);
	return true;
}