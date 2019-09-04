#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_vli ;
struct TYPE_3__ {int /*<<< orphan*/  uncompressed_size; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */

__attribute__((used)) static void
lzma_decoder_uncompressed(lzma_coder *coder, lzma_vli uncompressed_size)
{
	coder->uncompressed_size = uncompressed_size;
}