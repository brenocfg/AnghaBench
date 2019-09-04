#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_llist ;
struct TYPE_4__ {char* value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ mime_header_entry ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* zend_llist_get_first (int /*<<< orphan*/ *) ; 
 TYPE_1__* zend_llist_get_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *php_mime_get_hdr_value(zend_llist header, char *key)
{
	mime_header_entry *entry;

	if (key == NULL) {
		return NULL;
	}

	entry = zend_llist_get_first(&header);
	while (entry) {
		if (!strcasecmp(entry->key, key)) {
			return entry->value;
		}
		entry = zend_llist_get_next(&header);
	}

	return NULL;
}