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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 

__attribute__((used)) static inline void memcpy_le32(void *dst, const void *src, unsigned int len)
{
#ifdef __LITTLE_ENDIAN
	memcpy(dst, src, len);
#else
	u32 *_dst = dst;
	const __le32 *_src = src;
	len /= 4;
	while (len-- > 0)
		*_dst++ = le32_to_cpu(*_src++);
#endif
}