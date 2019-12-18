#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_11__ {int /*<<< orphan*/  file; } ;
struct TYPE_10__ {int file_count; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RBinXtrData ;
typedef  TYPE_2__ RBin ;

/* Variables and functions */
 int /*<<< orphan*/  load (TYPE_2__*) ; 
 TYPE_1__* oneshot (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_bin_xtrdata_free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/  (*) (TYPE_1__*)) ; 

__attribute__((used)) static RList * oneshotall(RBin *bin, const ut8* buf, ut64 size) {
	RBinXtrData *data = NULL;
	RList *res = NULL;
	int nlib, i = 0;
	if (!bin->file) {
		if (!load (bin)) {
			return NULL;
		}
	}
	data = oneshot (bin, buf, size, i);
	if (!data) {
		return res;
	}
	// XXX - how do we validate a valid nlib?
	nlib = data->file_count;
	res = r_list_newf (r_bin_xtrdata_free);
	if (!res) {
		r_bin_xtrdata_free (data);
		return NULL;
	}
	r_list_append (res, data);
	for (i = 1; data && i < nlib; i++) {
		data = oneshot (bin, buf, size, i);
		r_list_append (res, data);
	}
	return res;
}