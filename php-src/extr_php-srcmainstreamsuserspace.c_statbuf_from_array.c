#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {void* st_ctime; void* st_mtime; void* st_atime; void* st_size; void* st_gid; void* st_uid; void* st_nlink; void* st_mode; void* st_ino; void* st_dev; } ;
struct TYPE_6__ {TYPE_1__ sb; } ;
typedef  TYPE_2__ php_stream_statbuf ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int) ; 
 void* zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int statbuf_from_array(zval *array, php_stream_statbuf *ssb)
{
	zval *elem;

#define STAT_PROP_ENTRY_EX(name, name2)                        \
	if (NULL != (elem = zend_hash_str_find(Z_ARRVAL_P(array), #name, sizeof(#name)-1))) {     \
		ssb->sb.st_##name2 = zval_get_long(elem);                                                      \
	}

#define STAT_PROP_ENTRY(name) STAT_PROP_ENTRY_EX(name,name)

	memset(ssb, 0, sizeof(php_stream_statbuf));
	STAT_PROP_ENTRY(dev);
	STAT_PROP_ENTRY(ino);
	STAT_PROP_ENTRY(mode);
	STAT_PROP_ENTRY(nlink);
	STAT_PROP_ENTRY(uid);
	STAT_PROP_ENTRY(gid);
#if HAVE_STRUCT_STAT_ST_RDEV
	STAT_PROP_ENTRY(rdev);
#endif
	STAT_PROP_ENTRY(size);
	STAT_PROP_ENTRY(atime);
	STAT_PROP_ENTRY(mtime);
	STAT_PROP_ENTRY(ctime);
#ifdef HAVE_STRUCT_STAT_ST_BLKSIZE
	STAT_PROP_ENTRY(blksize);
#endif
#ifdef HAVE_STRUCT_STAT_ST_BLOCKS
	STAT_PROP_ENTRY(blocks);
#endif

#undef STAT_PROP_ENTRY
#undef STAT_PROP_ENTRY_EX
	return SUCCESS;
}