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
struct michael_mic {int r; int l; } ;

/* Variables and functions */
 int rol32 (int,int) ; 
 int ror32 (int,int) ; 

__attribute__((used)) static inline void michael_block(struct michael_mic *mic)
{
	mic->r ^= rol32(mic->l, 17);
	mic->l += mic->r;
	mic->r ^= ((mic->l & 0xff00ff00) >> 8) |
		  ((mic->l & 0x00ff00ff) << 8);
	mic->l += mic->r;
	mic->r ^= rol32(mic->l, 3);
	mic->l += mic->r;
	mic->r ^= ror32(mic->l, 2);
	mic->l += mic->r;
}