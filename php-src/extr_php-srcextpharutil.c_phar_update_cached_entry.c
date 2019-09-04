#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/ * s; } ;
struct TYPE_4__ {char* filename; TYPE_1__ metadata_str; int /*<<< orphan*/  metadata; scalar_t__ metadata_len; scalar_t__ is_persistent; scalar_t__ filename_len; void* tmp; void* link; int /*<<< orphan*/ * phar; } ;
typedef  TYPE_2__ phar_entry_info ;
typedef  int /*<<< orphan*/  phar_archive_data ;

/* Variables and functions */
 scalar_t__ IS_UNDEF ; 
 int ZEND_HASH_APPLY_KEEP ; 
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* estrdup (void*) ; 
 void* estrndup (char*,scalar_t__) ; 
 int /*<<< orphan*/  phar_parse_metadata (char**,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zval_copy_ctor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_update_cached_entry(zval *data, void *argument) /* {{{ */
{
	phar_entry_info *entry = (phar_entry_info *)Z_PTR_P(data);

	entry->phar = (phar_archive_data *)argument;

	if (entry->link) {
		entry->link = estrdup(entry->link);
	}

	if (entry->tmp) {
		entry->tmp = estrdup(entry->tmp);
	}

	entry->metadata_str.s = NULL;
	entry->filename = estrndup(entry->filename, entry->filename_len);
	entry->is_persistent = 0;

	if (Z_TYPE(entry->metadata) != IS_UNDEF) {
		if (entry->metadata_len) {
			char *buf = estrndup((char *) Z_PTR(entry->metadata), entry->metadata_len);
			/* assume success, we would have failed before */
			phar_parse_metadata((char **) &buf, &entry->metadata, entry->metadata_len);
			efree(buf);
		} else {
			zval_copy_ctor(&entry->metadata);
			entry->metadata_str.s = NULL;
		}
	}
	return ZEND_HASH_APPLY_KEEP;
}