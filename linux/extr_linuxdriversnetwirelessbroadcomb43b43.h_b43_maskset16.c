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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int b43_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int) ; 

__attribute__((used)) static inline void b43_maskset16(struct b43_wldev *dev, u16 offset, u16 mask,
				 u16 set)
{
	b43_write16(dev, offset, (b43_read16(dev, offset) & mask) | set);
}