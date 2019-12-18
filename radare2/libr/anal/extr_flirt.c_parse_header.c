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
struct TYPE_3__ {unsigned char version; unsigned char arch; unsigned char* ctype; int /*<<< orphan*/  ctypes_crc16; int /*<<< orphan*/  library_name_len; int /*<<< orphan*/  crc16; int /*<<< orphan*/  old_n_functions; int /*<<< orphan*/  features; int /*<<< orphan*/  app_types; int /*<<< orphan*/  os_types; int /*<<< orphan*/  file_types; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ idasig_v5_t ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_buf_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int parse_header(RBuffer *buf, idasig_v5_t *header) {
	if (r_buf_read_at (buf, 0, header->magic, sizeof(header->magic)) != sizeof(header->magic)) {
		return false;
	}
	if (r_buf_read (buf, &header->version, sizeof(header->version)) != sizeof(header->version)) {
		return false;
	}
	if (r_buf_read (buf, &header->arch, sizeof(header->arch)) != sizeof(header->arch)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->file_types, sizeof(header->file_types)) != sizeof(header->file_types)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->os_types, sizeof(header->os_types)) != sizeof(header->os_types)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->app_types, sizeof(header->app_types)) != sizeof(header->app_types)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->features, sizeof(header->features)) != sizeof(header->features)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->old_n_functions, sizeof(header->old_n_functions)) != sizeof(header->old_n_functions)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->crc16, sizeof(header->crc16)) != sizeof(header->crc16)) {
		return false;
	}
	if (r_buf_read (buf, header->ctype, sizeof(header->ctype)) != sizeof(header->ctype)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->library_name_len, sizeof(header->library_name_len)) != sizeof(header->library_name_len)) {
		return false;
	}
	if (r_buf_read (buf, (unsigned char *)&header->ctypes_crc16, sizeof(header->ctypes_crc16)) != sizeof(header->ctypes_crc16)) {
		return false;
	}

	return true;
}