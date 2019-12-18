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
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_6__ {void* uncompressed_size; void* compressed_size; } ;
struct TYPE_5__ {TYPE_2__ block_options; int /*<<< orphan*/  block_encoder; } ;
typedef  TYPE_1__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 void* LZMA_VLI_UNKNOWN ; 
 int /*<<< orphan*/  lzma_block_encoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lzma_block_header_size (TYPE_2__*) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_ret
block_encoder_init(lzma_coder *coder, lzma_allocator *allocator)
{
	// Prepare the Block options. Even though Block encoder doesn't need
	// compressed_size, uncompressed_size, and header_size to be
	// initialized, it is a good idea to do it here, because this way
	// we catch if someone gave us Filter ID that cannot be used in
	// Blocks/Streams.
	coder->block_options.compressed_size = LZMA_VLI_UNKNOWN;
	coder->block_options.uncompressed_size = LZMA_VLI_UNKNOWN;

	return_if_error(lzma_block_header_size(&coder->block_options));

	// Initialize the actual Block encoder.
	return lzma_block_encoder_init(&coder->block_encoder, allocator,
			&coder->block_options);
}