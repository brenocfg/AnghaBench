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
typedef  TYPE_1__ SCV_NB10_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int const) ; 
 scalar_t__ strdup (char const*) ; 

__attribute__((used)) static void get_nb10(ut8* dbg_data, int dbg_data_len, SCV_NB10_HEADER* res) {
	const int nb10sz = 16;
	if (dbg_data_len < nb10sz) {
		return;
	}
	memcpy (res, dbg_data, nb10sz);
	res->file_name = (ut8*) strdup ((const char*) dbg_data + nb10sz);
}