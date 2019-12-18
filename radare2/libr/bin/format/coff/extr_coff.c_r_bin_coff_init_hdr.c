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
typedef  int ut16 ;
struct TYPE_2__ {scalar_t__ f_magic; } ;
struct r_bin_coff_obj {scalar_t__ endian; int /*<<< orphan*/  target_id; int /*<<< orphan*/  b; TYPE_1__ hdr; } ;
struct coff_hdr {int dummy; } ;

/* Variables and functions */
#define  COFF_FILE_MACHINE_AMD29KBE 129 
#define  COFF_FILE_MACHINE_H8300 128 
 scalar_t__ COFF_FILE_TI_COFF ; 
 scalar_t__ COFF_IS_BIG_ENDIAN ; 
 scalar_t__ COFF_IS_LITTLE_ENDIAN ; 
 int r_buf_fread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_fread_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_read_ble16_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool r_bin_coff_init_hdr(struct r_bin_coff_obj *obj) {
	ut16 magic = r_buf_read_ble16_at (obj->b, 0, COFF_IS_LITTLE_ENDIAN);
	switch (magic) {
	case COFF_FILE_MACHINE_H8300:
	case COFF_FILE_MACHINE_AMD29KBE:
		obj->endian = COFF_IS_BIG_ENDIAN;
		break;
	default:
		obj->endian = COFF_IS_LITTLE_ENDIAN;
	}
	int ret = 0;
	ret = r_buf_fread_at (obj->b, 0, (ut8 *)&obj->hdr, obj->endian? "2S3I2S": "2s3i2s", 1);
	if (ret != sizeof (struct coff_hdr)) {
		return false;
	}
	if (obj->hdr.f_magic == COFF_FILE_TI_COFF) {
		ret = r_buf_fread (obj->b, (ut8 *)&obj->target_id, obj->endian? "S": "s", 1);
		if (ret != sizeof (ut16)) {
			return false;
		}
	}
	return true;
}