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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBinXtrData ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 int /*<<< orphan*/  SUB_BIN_DOS ; 
 int /*<<< orphan*/  SUB_BIN_NATIVE ; 
 int /*<<< orphan*/  SUB_BIN_NET ; 
 int /*<<< orphan*/ * oneshot (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_bin_xtrdata_free ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RList * oneshotall(RBin *bin, const ut8 *buf, ut64 size) {
	//extract dos componenent first
	RBinXtrData *data = oneshot (bin, buf, size, SUB_BIN_DOS);

	if (!data) {
		return NULL;
	}
	// XXX - how do we validate a valid narch?
	RList * res = r_list_newf (r_bin_xtrdata_free);
	r_list_append (res, data);

	if ((data = oneshot (bin, buf, size, SUB_BIN_NATIVE))){
		r_list_append (res, data);
	}

	if ((data = oneshot (bin, buf, size, SUB_BIN_NET))){
		r_list_append (res, data);
	}

	return res;
}