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
typedef  int /*<<< orphan*/  ut64 ;
struct r_bin_mdmp_obj {int /*<<< orphan*/  kv; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 struct r_bin_mdmp_obj* r_bin_mdmp_new_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdb_ns_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool load_buffer(RBinFile *bf, void **bin_obj, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	r_return_val_if_fail (buf, false);
	struct r_bin_mdmp_obj *res = r_bin_mdmp_new_buf (buf);
	if (res) {
		sdb_ns_set (sdb, "info", res->kv);
		*bin_obj = res;
		return true;
	}
	return false;
}