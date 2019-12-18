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
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  Max (int,int) ; 
 int /*<<< orphan*/  Min (int,int /*<<< orphan*/ ) ; 
 int NBuffers ; 

Size
CLOGShmemBuffers(void)
{
	return Min(128, Max(4, NBuffers / 512));
}