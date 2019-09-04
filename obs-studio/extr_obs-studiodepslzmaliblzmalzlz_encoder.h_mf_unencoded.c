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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ read_ahead; scalar_t__ read_pos; scalar_t__ write_pos; } ;
typedef  TYPE_1__ lzma_mf ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
mf_unencoded(const lzma_mf *mf)
{
	return mf->write_pos - mf->read_pos + mf->read_ahead;
}