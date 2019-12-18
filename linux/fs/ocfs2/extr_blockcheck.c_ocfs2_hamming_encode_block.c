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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_hamming_encode (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 

u32 ocfs2_hamming_encode_block(void *data, unsigned int blocksize)
{
	return ocfs2_hamming_encode(0, data, blocksize * 8, 0);
}