#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct r_bin_java_obj_t {int /*<<< orphan*/  file; } ;
struct TYPE_3__ {scalar_t__ file; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  add_bin_obj_to_sdb (struct r_bin_java_obj_t*) ; 
 struct r_bin_java_obj_t* r_bin_java_new_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 

__attribute__((used)) static bool load_buffer(RBinFile * bf, void **bin_obj, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	struct r_bin_java_obj_t *tmp_bin_obj = NULL;
	RBuffer *tbuf = r_buf_ref (buf);
	tmp_bin_obj = r_bin_java_new_buf (tbuf, loadaddr, sdb);
	if (!tmp_bin_obj) {
		return false;
	}
	*bin_obj = tmp_bin_obj;
	add_bin_obj_to_sdb (tmp_bin_obj);
	if (bf && bf->file) {
		tmp_bin_obj->file = strdup (bf->file);
	}
	r_buf_free (tbuf);
	return true;
}