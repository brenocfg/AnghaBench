#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int file_count; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RBinXtrData ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 TYPE_1__* extract (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_bin_xtrdata_free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/  (*) (TYPE_1__*)) ; 

__attribute__((used)) static RList * extractall(RBin *bin) {
	RList *res = NULL;
	int narch, i = 0;
	RBinXtrData *data = NULL;

	data = extract (bin, i);
	if (!data) {
		return res;
	}

	// XXX - how do we validate a valid narch?
	narch = data->file_count;
	res = r_list_newf (r_bin_xtrdata_free);
	if (!res) {
		r_bin_xtrdata_free (data);
		return NULL;
	}
	r_list_append (res, data);
	for (i = 1; data && i < narch; i++) {
		data = extract (bin, i);
		r_list_append (res, data);
	}
	return res;
}