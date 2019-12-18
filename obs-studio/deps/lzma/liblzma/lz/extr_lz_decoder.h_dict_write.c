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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ pos; scalar_t__ full; int /*<<< orphan*/  limit; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ lzma_dict ;

/* Variables and functions */
 scalar_t__ lzma_bufcpy (int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
dict_write(lzma_dict *restrict dict, const uint8_t *restrict in,
		size_t *restrict in_pos, size_t in_size,
		size_t *restrict left)
{
	// NOTE: If we are being given more data than the size of the
	// dictionary, it could be possible to optimize the LZ decoder
	// so that not everything needs to go through the dictionary.
	// This shouldn't be very common thing in practice though, and
	// the slowdown of one extra memcpy() isn't bad compared to how
	// much time it would have taken if the data were compressed.

	if (in_size - *in_pos > *left)
		in_size = *in_pos + *left;

	*left -= lzma_bufcpy(in, in_pos, in_size,
			dict->buf, &dict->pos, dict->limit);

	if (dict->pos > dict->full)
		dict->full = dict->pos;

	return;
}