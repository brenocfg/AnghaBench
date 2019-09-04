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
struct TYPE_3__ {int /*<<< orphan*/  vaddr; } ;
typedef  TYPE_1__ vaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32_rep (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static inline void mga_memcpy_toio(vaddr_t va, const void* src, int len) {
#if defined(__alpha__) || defined(__i386__) || defined(__x86_64__)
	/*
	 * iowrite32_rep works for us if:
	 *  (1) Copies data as 32bit quantities, not byte after byte,
	 *  (2) Performs LE ordered stores, and
	 *  (3) It copes with unaligned source (destination is guaranteed to be page
	 *      aligned and length is guaranteed to be multiple of 4).
	 */
	iowrite32_rep(va.vaddr, src, len >> 2);
#else
        u_int32_t __iomem* addr = va.vaddr;

	if ((unsigned long)src & 3) {
		while (len >= 4) {
			fb_writel(get_unaligned((u32 *)src), addr);
			addr++;
			len -= 4;
			src += 4;
		}
	} else {
		while (len >= 4) {
			fb_writel(*(u32 *)src, addr);
			addr++;
			len -= 4;
			src += 4;
		}
	}
#endif
}