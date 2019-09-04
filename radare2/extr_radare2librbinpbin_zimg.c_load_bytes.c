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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 void* r_bin_zimg_new_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new_with_bytes (int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static bool load_bytes(RBinFile *bf, void **bin_obj, const ut8 *buf, ut64 size, ut64 loadaddr, Sdb *sdb){
	void *res = NULL;
	RBuffer *tbuf = NULL;
	if (!buf || size == 0 || size == UT64_MAX) {
		return false;
	}
	tbuf = r_buf_new_with_bytes (buf, size);
	if (!tbuf) {
		return false;
	}
	res = r_bin_zimg_new_buf (tbuf);
	r_buf_free (tbuf);
	*bin_obj = res;
	return true;
}