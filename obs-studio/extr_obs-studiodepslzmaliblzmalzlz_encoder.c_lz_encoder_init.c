#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {size_t const size; int write_pos; size_t hash_size_sum; size_t sons_count; int /*<<< orphan*/  action; int /*<<< orphan*/  (* skip ) (TYPE_1__*,int) ;int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * hash; scalar_t__ cyclic_pos; int /*<<< orphan*/  son; scalar_t__ pending; scalar_t__ read_limit; scalar_t__ read_ahead; scalar_t__ read_pos; int /*<<< orphan*/  cyclic_size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ lzma_mf ;
struct TYPE_7__ {scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; } ;
typedef  TYPE_2__ lzma_lz_options ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_RUN ; 
 int /*<<< orphan*/  LZMA_SYNC_FLUSH ; 
 int SIZE_MAX ; 
 void* lzma_alloc (size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,size_t) ; 
 int my_min (scalar_t__,size_t const) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static bool
lz_encoder_init(lzma_mf *mf, lzma_allocator *allocator,
		const lzma_lz_options *lz_options)
{
	// Allocate the history buffer.
	if (mf->buffer == NULL) {
		mf->buffer = lzma_alloc(mf->size, allocator);
		if (mf->buffer == NULL)
			return true;
	}

	// Use cyclic_size as initial mf->offset. This allows
	// avoiding a few branches in the match finders. The downside is
	// that match finder needs to be normalized more often, which may
	// hurt performance with huge dictionaries.
	mf->offset = mf->cyclic_size;
	mf->read_pos = 0;
	mf->read_ahead = 0;
	mf->read_limit = 0;
	mf->write_pos = 0;
	mf->pending = 0;

	// Allocate match finder's hash array.
	const size_t alloc_count = mf->hash_size_sum + mf->sons_count;

#if UINT32_MAX >= SIZE_MAX / 4
	// Check for integer overflow. (Huge dictionaries are not
	// possible on 32-bit CPU.)
	if (alloc_count > SIZE_MAX / sizeof(uint32_t))
		return true;
#endif

	if (mf->hash == NULL) {
		mf->hash = lzma_alloc(alloc_count * sizeof(uint32_t),
				allocator);
		if (mf->hash == NULL)
			return true;
	}

	mf->son = mf->hash + mf->hash_size_sum;
	mf->cyclic_pos = 0;

	// Initialize the hash table. Since EMPTY_HASH_VALUE is zero, we
	// can use memset().
/*
	for (uint32_t i = 0; i < hash_size_sum; ++i)
		mf->hash[i] = EMPTY_HASH_VALUE;
*/
	memzero(mf->hash, (size_t)(mf->hash_size_sum) * sizeof(uint32_t));

	// We don't need to initialize mf->son, but not doing that will
	// make Valgrind complain in normalization (see normalize() in
	// lz_encoder_mf.c).
	//
	// Skipping this initialization is *very* good when big dictionary is
	// used but only small amount of data gets actually compressed: most
	// of the mf->hash won't get actually allocated by the kernel, so
	// we avoid wasting RAM and improve initialization speed a lot.
	//memzero(mf->son, (size_t)(mf->sons_count) * sizeof(uint32_t));

	// Handle preset dictionary.
	if (lz_options->preset_dict != NULL
			&& lz_options->preset_dict_size > 0) {
		// If the preset dictionary is bigger than the actual
		// dictionary, use only the tail.
		mf->write_pos = my_min(lz_options->preset_dict_size, mf->size);
		memcpy(mf->buffer, lz_options->preset_dict
				+ lz_options->preset_dict_size - mf->write_pos,
				mf->write_pos);
		mf->action = LZMA_SYNC_FLUSH;
		mf->skip(mf, mf->write_pos);
	}

	mf->action = LZMA_RUN;

	return false;
}