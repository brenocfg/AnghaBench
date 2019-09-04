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
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X1 ; 
 int /*<<< orphan*/  X2 ; 

__attribute__((used)) static void rlock_AA3(void)
{
	WL(X1);
	RL(X2); // this one should fail
}