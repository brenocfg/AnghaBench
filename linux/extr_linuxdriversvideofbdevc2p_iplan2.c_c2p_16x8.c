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
 int /*<<< orphan*/  transp4 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  transp4x (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void c2p_16x8(u32 d[4])
{
	transp4(d, 8, 2);
	transp4(d, 1, 2);
	transp4x(d, 16, 2);
	transp4x(d, 2, 2);
	transp4(d, 4, 1);
}