#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_5__ {int /*<<< orphan*/  perms; int /*<<< orphan*/  size; int /*<<< orphan*/  crc32; } ;
typedef  TYPE_1__ phar_zip_unix3 ;
struct TYPE_6__ {char* tag; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ phar_zip_extra_field_header ;
struct TYPE_7__ {int flags; scalar_t__ is_dir; } ;
typedef  TYPE_3__ phar_entry_info ;

/* Variables and functions */
 int FAILURE ; 
 int PHAR_ENT_COMPRESSION_MASK ; 
 int PHAR_ENT_PERM_MASK ; 
 int PHAR_GET_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int SUCCESS ; 
 int php_stream_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phar_zip_process_extra(php_stream *fp, phar_entry_info *entry, uint16_t len) /* {{{ */
{
	union {
		phar_zip_extra_field_header header;
		phar_zip_unix3 unix3;
	} h;
	size_t read;

	do {
		if (sizeof(h.header) != php_stream_read(fp, (char *) &h.header, sizeof(h.header))) {
			return FAILURE;
		}

		if (h.header.tag[0] != 'n' || h.header.tag[1] != 'u') {
			/* skip to next header */
			php_stream_seek(fp, PHAR_GET_16(h.header.size), SEEK_CUR);
			len -= PHAR_GET_16(h.header.size) + 4;
			continue;
		}

		/* unix3 header found */
		read = php_stream_read(fp, (char *) &(h.unix3.crc32), sizeof(h.unix3) - sizeof(h.header));
		len -= read + 4;

		if (sizeof(h.unix3) - sizeof(h.header) != read) {
			return FAILURE;
		}

		if (PHAR_GET_16(h.unix3.size) > sizeof(h.unix3) - 4) {
			/* skip symlink filename - we may add this support in later */
			php_stream_seek(fp, PHAR_GET_16(h.unix3.size) - sizeof(h.unix3.size), SEEK_CUR);
		}

		/* set permissions */
		entry->flags &= PHAR_ENT_COMPRESSION_MASK;

		if (entry->is_dir) {
			entry->flags |= PHAR_GET_16(h.unix3.perms) & PHAR_ENT_PERM_MASK;
		} else {
			entry->flags |= PHAR_GET_16(h.unix3.perms) & PHAR_ENT_PERM_MASK;
		}

	} while (len);

	return SUCCESS;
}