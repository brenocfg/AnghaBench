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
typedef  int /*<<< orphan*/  lzma_index ;
struct TYPE_3__ {scalar_t__ crc32; scalar_t__ pos; int /*<<< orphan*/  const* index; int /*<<< orphan*/  sequence; int /*<<< orphan*/  iter; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_INDICATOR ; 
 int /*<<< orphan*/  lzma_index_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
index_encoder_reset(lzma_coder *coder, const lzma_index *i)
{
	lzma_index_iter_init(&coder->iter, i);

	coder->sequence = SEQ_INDICATOR;
	coder->index = i;
	coder->pos = 0;
	coder->crc32 = 0;

	return;
}