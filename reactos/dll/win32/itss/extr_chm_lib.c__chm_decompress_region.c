#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t block_len; } ;
struct chmFile {size_t* cache_block_indices; size_t cache_num_blocks; int lzx_last_block; int /*<<< orphan*/  lzx_mutex; int /*<<< orphan*/  window_size; scalar_t__ lzx_state; int /*<<< orphan*/  cache_mutex; int /*<<< orphan*/ ** cache_blocks; TYPE_1__ reset_table; } ;
typedef  size_t UInt64 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  scalar_t__ Int64 ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHM_RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ LZXinit (int /*<<< orphan*/ ) ; 
 size_t _chm_decompress_block (struct chmFile*,size_t,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static Int64 _chm_decompress_region(struct chmFile *h,
                                    UChar *buf,
                                    UInt64 start,
                                    Int64 len)
{
    UInt64 nBlock, nOffset;
    UInt64 nLen;
    UInt64 gotLen;
    UChar *ubuffer = NULL;

        if (len <= 0)
                return 0;

    /* figure out what we need to read */
    nBlock = start / h->reset_table.block_len;
    nOffset = start % h->reset_table.block_len;
    nLen = len;
    if (nLen > (h->reset_table.block_len - nOffset))
        nLen = h->reset_table.block_len - nOffset;

    /* if block is cached, return data from it. */
    CHM_ACQUIRE_LOCK(h->lzx_mutex);
    CHM_ACQUIRE_LOCK(h->cache_mutex);
    if (h->cache_block_indices[nBlock % h->cache_num_blocks] == nBlock    &&
        h->cache_blocks[nBlock % h->cache_num_blocks] != NULL)
    {
        memcpy(buf,
               h->cache_blocks[nBlock % h->cache_num_blocks] + nOffset,
               (unsigned int)nLen);
        CHM_RELEASE_LOCK(h->cache_mutex);
        CHM_RELEASE_LOCK(h->lzx_mutex);
        return nLen;
    }
    CHM_RELEASE_LOCK(h->cache_mutex);

    /* data request not satisfied, so... start up the decompressor machine */
    if (! h->lzx_state)
    {
        h->lzx_last_block = -1;
        h->lzx_state = LZXinit(h->window_size);
    }

    /* decompress some data */
    gotLen = _chm_decompress_block(h, nBlock, &ubuffer);
    if (gotLen < nLen)
        nLen = gotLen;
    memcpy(buf, ubuffer+nOffset, (unsigned int)nLen);
    CHM_RELEASE_LOCK(h->lzx_mutex);
    return nLen;
}