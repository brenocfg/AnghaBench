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
 int /*<<< orphan*/  SecureZeroMemory (void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void
secure_memzero(void *data, size_t len)
{
#if defined(_WIN32)
    SecureZeroMemory(data, len);
#elif defined(__GNUC__) || defined(__clang__)
    memset(data, 0, len);
    __asm__ __volatile__ ("" : : "r" (data) : "memory");
#else
    volatile char *p = (volatile char *) data;
    while (len--)
    {
        *p++ = 0;
    }
#endif
}