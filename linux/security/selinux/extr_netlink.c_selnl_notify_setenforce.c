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
 int /*<<< orphan*/  SELNL_MSG_SETENFORCE ; 
 int /*<<< orphan*/  selnl_notify (int /*<<< orphan*/ ,int*) ; 

void selnl_notify_setenforce(int val)
{
	selnl_notify(SELNL_MSG_SETENFORCE, &val);
}