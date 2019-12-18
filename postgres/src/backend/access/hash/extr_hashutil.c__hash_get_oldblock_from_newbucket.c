#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int Bucket ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_TO_BLKNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_METAPAGE ; 
 int /*<<< orphan*/  HASH_READ ; 
 int /*<<< orphan*/  HashPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LH_META_PAGE ; 
 int /*<<< orphan*/  _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fls (int) ; 

BlockNumber
_hash_get_oldblock_from_newbucket(Relation rel, Bucket new_bucket)
{
	Bucket		old_bucket;
	uint32		mask;
	Buffer		metabuf;
	HashMetaPage metap;
	BlockNumber blkno;

	/*
	 * To get the old bucket from the current bucket, we need a mask to modulo
	 * into lower half of table.  This mask is stored in meta page as
	 * hashm_lowmask, but here we can't rely on the same, because we need a
	 * value of lowmask that was prevalent at the time when bucket split was
	 * started.  Masking the most significant bit of new bucket would give us
	 * old bucket.
	 */
	mask = (((uint32) 1) << (fls(new_bucket) - 1)) - 1;
	old_bucket = new_bucket & mask;

	metabuf = _hash_getbuf(rel, HASH_METAPAGE, HASH_READ, LH_META_PAGE);
	metap = HashPageGetMeta(BufferGetPage(metabuf));

	blkno = BUCKET_TO_BLKNO(metap, old_bucket);

	_hash_relbuf(rel, metabuf);

	return blkno;
}