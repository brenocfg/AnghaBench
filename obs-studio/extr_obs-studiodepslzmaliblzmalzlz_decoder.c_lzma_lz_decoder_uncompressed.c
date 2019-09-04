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
typedef  int /*<<< orphan*/  lzma_vli ;
struct TYPE_4__ {int /*<<< orphan*/  coder; int /*<<< orphan*/  (* set_uncompressed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ lz; } ;
typedef  TYPE_2__ lzma_coder ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern void
lzma_lz_decoder_uncompressed(lzma_coder *coder, lzma_vli uncompressed_size)
{
	coder->lz.set_uncompressed(coder->lz.coder, uncompressed_size);
}