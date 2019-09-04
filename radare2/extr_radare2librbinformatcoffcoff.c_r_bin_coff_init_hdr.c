#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut16 ;
struct TYPE_2__ {scalar_t__ f_magic; } ;
struct r_bin_coff_obj {int endian; int /*<<< orphan*/  target_id; int /*<<< orphan*/  b; TYPE_1__ hdr; } ;
struct coff_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ COFF_FILE_MACHINE_H8300 ; 
 scalar_t__ COFF_FILE_TI_COFF ; 
 int /*<<< orphan*/  R_BUF_CUR ; 
 int r_buf_fread_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ r_buf_read_ble16_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool r_bin_coff_init_hdr(struct r_bin_coff_obj *obj) {
	ut16 magic = r_buf_read_ble16_at (obj->b, 0, obj->endian);;
	obj->endian = (magic == COFF_FILE_MACHINE_H8300)? 1 : 0;
	int ret = 0;
	ret = r_buf_fread_at (obj->b, 0, (ut8 *)&obj->hdr, obj->endian? "2S3I2S": "2s3i2s", 1);
	if (ret != sizeof (struct coff_hdr)) {
		return false;
	}
	if (obj->hdr.f_magic == COFF_FILE_TI_COFF) {
		ret = r_buf_fread_at (obj->b, R_BUF_CUR, (ut8 *)&obj->target_id, obj->endian? "S": "s", 1);
		if (ret != sizeof (ut16)) {
			return false;
		}
	}
	return true;
}