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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int LZ4_decompress_safe (char const*,char*,int,int) ; 

__attribute__((used)) static uint32_t decompress(const ut8 *cbuf, ut8 *obuf, int32_t csize, int32_t usize) {
	if (csize < 0 || usize < 0 || !cbuf || !obuf) {
		return -1;
	}
	return LZ4_decompress_safe ((const char*)cbuf, (char*)obuf, (uint32_t) csize, (uint32_t) usize);
}