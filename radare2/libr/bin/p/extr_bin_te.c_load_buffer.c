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
typedef  scalar_t__ ut64 ;
struct r_bin_te_obj_t {int /*<<< orphan*/  kv; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 struct r_bin_te_obj_t* r_bin_te_new_buf (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdb_ns_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool load_buffer(RBinFile *bf, void **bin_obj, RBuffer *b, ut64 loadaddr, Sdb *sdb) {
	r_return_val_if_fail (bf && bin_obj && b, false);
	ut64 sz = r_buf_size (b);
	if (sz == 0 || sz == UT64_MAX) {
		return false;
	}
	struct r_bin_te_obj_t *res = r_bin_te_new_buf (b);
	if (res) {
		sdb_ns_set (sdb, "info", res->kv);
	}
	*bin_obj = res;
	return true;
}