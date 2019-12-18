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
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wined3d_pause(void)
{
#ifdef __REACTOS__
    Sleep(0);
#else
#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__( "rep;nop" : : : "memory" );
#endif
#endif
}