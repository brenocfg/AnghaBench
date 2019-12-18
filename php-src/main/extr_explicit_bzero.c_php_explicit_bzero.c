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

/* Variables and functions */
 int /*<<< orphan*/  RtlSecureZeroMemory (void*,size_t) ; 
 int /*<<< orphan*/  explicit_memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void php_explicit_bzero(void *dst, size_t siz)
{
#if HAVE_EXPLICIT_MEMSET
    explicit_memset(dst, 0, siz);
#elif defined(PHP_WIN32)
	RtlSecureZeroMemory(dst, siz);
#elif defined(__GNUC__)
	memset(dst, 0, siz);
	asm __volatile__("" :: "r"(dst) : "memory");
#else
	size_t i = 0;
	volatile unsigned char *buf = (volatile unsigned char *)dst;

	for (; i < siz; i ++)
		buf[i] = 0;
#endif
}