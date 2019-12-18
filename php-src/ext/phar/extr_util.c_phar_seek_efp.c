#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_off_t ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_7__ {scalar_t__ uncompressed_filesize; scalar_t__ is_dir; } ;
typedef  TYPE_1__ phar_entry_info ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/ * phar_get_efp (TYPE_1__*,int) ; 
 scalar_t__ phar_get_fp_offset (TYPE_1__*) ; 
 TYPE_1__* phar_get_link_source (TYPE_1__*) ; 
 int php_stream_seek (int /*<<< orphan*/ *,scalar_t__,int const) ; 

int phar_seek_efp(phar_entry_info *entry, zend_off_t offset, int whence, zend_off_t position, int follow_links) /* {{{ */
{
	php_stream *fp = phar_get_efp(entry, follow_links);
	zend_off_t temp, eoffset;

	if (!fp) {
		return -1;
	}

	if (follow_links) {
		phar_entry_info *t;
		t = phar_get_link_source(entry);
		if (t) {
			entry = t;
		}
	}

	if (entry->is_dir) {
		return 0;
	}

	eoffset = phar_get_fp_offset(entry);

	switch (whence) {
		case SEEK_END:
			temp = eoffset + entry->uncompressed_filesize + offset;
			break;
		case SEEK_CUR:
			temp = eoffset + position + offset;
			break;
		case SEEK_SET:
			temp = eoffset + offset;
			break;
		default:
			temp = 0;
	}

	if (temp > eoffset + (zend_off_t) entry->uncompressed_filesize) {
		return -1;
	}

	if (temp < eoffset) {
		return -1;
	}

	return php_stream_seek(fp, temp, SEEK_SET);
}