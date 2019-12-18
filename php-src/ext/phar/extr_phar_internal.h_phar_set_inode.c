#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t filename_len; unsigned short inode; int /*<<< orphan*/  filename; TYPE_1__* phar; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_4__ {size_t fname_len; int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ zend_hash_func (char*,size_t) ; 

__attribute__((used)) static inline void phar_set_inode(phar_entry_info *entry) /* {{{ */
{
	char tmp[MAXPATHLEN];
	size_t tmp_len;
	size_t len1, len2;

	tmp_len = MIN(MAXPATHLEN, entry->filename_len + entry->phar->fname_len);

	len1 = MIN(entry->phar->fname_len, tmp_len);
	if (entry->phar->fname) {
		memcpy(tmp, entry->phar->fname, len1);
	}

	len2 = MIN(tmp_len - len1, entry->filename_len);
	memcpy(tmp + len1, entry->filename, len2);

	entry->inode = (unsigned short) zend_hash_func(tmp, tmp_len);
}