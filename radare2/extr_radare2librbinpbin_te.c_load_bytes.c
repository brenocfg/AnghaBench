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
struct r_bin_te_obj_t {int /*<<< orphan*/  kv; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 struct r_bin_te_obj_t* r_bin_te_new_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int /*<<< orphan*/  r_buf_set_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ns_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool load_bytes(RBinFile *bf, void **bin_obj, const ut8 *buf, ut64 sz, ut64 loadaddr, Sdb *sdb){
	struct r_bin_te_obj_t *res = NULL;
	RBuffer *tbuf = NULL;

	if (!buf || sz == 0 || sz == UT64_MAX) {
		return false;
	}
	tbuf = r_buf_new ();
	r_buf_set_bytes (tbuf, buf, sz);
	res = r_bin_te_new_buf (tbuf);
	if (res) {
		sdb_ns_set (sdb, "info", res->kv);
	}
	r_buf_free (tbuf);
	*bin_obj = res;
	return true;
}