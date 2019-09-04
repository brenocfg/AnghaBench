#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* link; TYPE_1__* phar; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_7__ {int /*<<< orphan*/  manifest; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (char*) ; 
 char* phar_get_link_location (TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_2__* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

phar_entry_info *phar_get_link_source(phar_entry_info *entry) /* {{{ */
{
	phar_entry_info *link_entry;
	char *link;

	if (!entry->link) {
		return entry;
	}

	link = phar_get_link_location(entry);
	if (NULL != (link_entry = zend_hash_str_find_ptr(&(entry->phar->manifest), entry->link, strlen(entry->link))) ||
		NULL != (link_entry = zend_hash_str_find_ptr(&(entry->phar->manifest), link, strlen(link)))) {
		if (link != entry->link) {
			efree(link);
		}
		return phar_get_link_source(link_entry);
	} else {
		if (link != entry->link) {
			efree(link);
		}
		return NULL;
	}
}