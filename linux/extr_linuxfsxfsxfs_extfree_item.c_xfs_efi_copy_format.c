#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ i_len; TYPE_3__* i_addr; } ;
typedef  TYPE_2__ xfs_log_iovec_t ;
typedef  int /*<<< orphan*/  xfs_extent_t ;
typedef  int /*<<< orphan*/  xfs_extent_64_t ;
typedef  int /*<<< orphan*/  xfs_extent_32_t ;
struct TYPE_10__ {int efi_nextents; TYPE_1__* efi_extents; int /*<<< orphan*/  efi_id; int /*<<< orphan*/  efi_size; int /*<<< orphan*/  efi_type; } ;
typedef  TYPE_3__ xfs_efi_log_format_t ;
typedef  TYPE_3__ xfs_efi_log_format_64_t ;
typedef  TYPE_3__ xfs_efi_log_format_32_t ;
typedef  scalar_t__ uint ;
struct TYPE_8__ {int /*<<< orphan*/  ext_len; int /*<<< orphan*/  ext_start; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 

int
xfs_efi_copy_format(xfs_log_iovec_t *buf, xfs_efi_log_format_t *dst_efi_fmt)
{
	xfs_efi_log_format_t *src_efi_fmt = buf->i_addr;
	uint i;
	uint len = sizeof(xfs_efi_log_format_t) + 
		(src_efi_fmt->efi_nextents - 1) * sizeof(xfs_extent_t);  
	uint len32 = sizeof(xfs_efi_log_format_32_t) + 
		(src_efi_fmt->efi_nextents - 1) * sizeof(xfs_extent_32_t);  
	uint len64 = sizeof(xfs_efi_log_format_64_t) + 
		(src_efi_fmt->efi_nextents - 1) * sizeof(xfs_extent_64_t);  

	if (buf->i_len == len) {
		memcpy((char *)dst_efi_fmt, (char*)src_efi_fmt, len);
		return 0;
	} else if (buf->i_len == len32) {
		xfs_efi_log_format_32_t *src_efi_fmt_32 = buf->i_addr;

		dst_efi_fmt->efi_type     = src_efi_fmt_32->efi_type;
		dst_efi_fmt->efi_size     = src_efi_fmt_32->efi_size;
		dst_efi_fmt->efi_nextents = src_efi_fmt_32->efi_nextents;
		dst_efi_fmt->efi_id       = src_efi_fmt_32->efi_id;
		for (i = 0; i < dst_efi_fmt->efi_nextents; i++) {
			dst_efi_fmt->efi_extents[i].ext_start =
				src_efi_fmt_32->efi_extents[i].ext_start;
			dst_efi_fmt->efi_extents[i].ext_len =
				src_efi_fmt_32->efi_extents[i].ext_len;
		}
		return 0;
	} else if (buf->i_len == len64) {
		xfs_efi_log_format_64_t *src_efi_fmt_64 = buf->i_addr;

		dst_efi_fmt->efi_type     = src_efi_fmt_64->efi_type;
		dst_efi_fmt->efi_size     = src_efi_fmt_64->efi_size;
		dst_efi_fmt->efi_nextents = src_efi_fmt_64->efi_nextents;
		dst_efi_fmt->efi_id       = src_efi_fmt_64->efi_id;
		for (i = 0; i < dst_efi_fmt->efi_nextents; i++) {
			dst_efi_fmt->efi_extents[i].ext_start =
				src_efi_fmt_64->efi_extents[i].ext_start;
			dst_efi_fmt->efi_extents[i].ext_len =
				src_efi_fmt_64->efi_extents[i].ext_len;
		}
		return 0;
	}
	return -EFSCORRUPTED;
}