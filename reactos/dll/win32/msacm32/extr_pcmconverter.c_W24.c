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
 unsigned char HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int) ; 
 unsigned char LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int) ; 

__attribute__((used)) static inline void  W24(unsigned char* dst, int s)
{
    dst[0] = HIBYTE(LOWORD(s));
    dst[1] = LOBYTE(HIWORD(s));
    dst[2] = HIBYTE(HIWORD(s));
}