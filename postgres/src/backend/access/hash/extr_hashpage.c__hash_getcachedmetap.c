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
struct TYPE_4__ {char* rd_amcache; int /*<<< orphan*/  rd_indexcxt; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  HashMetaPageData ;
typedef  int /*<<< orphan*/  HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_METAPAGE ; 
 int /*<<< orphan*/  HASH_READ ; 
 int /*<<< orphan*/  HashPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LH_META_PAGE ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_getbuf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

HashMetaPage
_hash_getcachedmetap(Relation rel, Buffer *metabuf, bool force_refresh)
{
	Page		page;

	Assert(metabuf);
	if (force_refresh || rel->rd_amcache == NULL)
	{
		char	   *cache = NULL;

		/*
		 * It's important that we don't set rd_amcache to an invalid value.
		 * Either MemoryContextAlloc or _hash_getbuf could fail, so don't
		 * install a pointer to the newly-allocated storage in the actual
		 * relcache entry until both have succeeded.
		 */
		if (rel->rd_amcache == NULL)
			cache = MemoryContextAlloc(rel->rd_indexcxt,
									   sizeof(HashMetaPageData));

		/* Read the metapage. */
		if (BufferIsValid(*metabuf))
			LockBuffer(*metabuf, BUFFER_LOCK_SHARE);
		else
			*metabuf = _hash_getbuf(rel, HASH_METAPAGE, HASH_READ,
									LH_META_PAGE);
		page = BufferGetPage(*metabuf);

		/* Populate the cache. */
		if (rel->rd_amcache == NULL)
			rel->rd_amcache = cache;
		memcpy(rel->rd_amcache, HashPageGetMeta(page),
			   sizeof(HashMetaPageData));

		/* Release metapage lock, but keep the pin. */
		LockBuffer(*metabuf, BUFFER_LOCK_UNLOCK);
	}

	return (HashMetaPage) rel->rd_amcache;
}