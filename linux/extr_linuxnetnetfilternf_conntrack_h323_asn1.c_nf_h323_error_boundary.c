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
struct bitstr {scalar_t__* cur; scalar_t__* end; scalar_t__ bit; } ;

/* Variables and functions */
 size_t BITS_PER_BYTE ; 

__attribute__((used)) static int nf_h323_error_boundary(struct bitstr *bs, size_t bytes, size_t bits)
{
	bits += bs->bit;
	bytes += bits / BITS_PER_BYTE;
	if (bits % BITS_PER_BYTE > 0)
		bytes++;

	if (*bs->cur + bytes > *bs->end)
		return 1;

	return 0;
}