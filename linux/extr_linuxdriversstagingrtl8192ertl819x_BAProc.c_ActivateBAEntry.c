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
typedef  scalar_t__ u16 ;
struct rtllib_device {int dummy; } ;
struct ba_record {int bValid; int /*<<< orphan*/  Timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void ActivateBAEntry(struct rtllib_device *ieee, struct ba_record *pBA,
			    u16 Time)
{
	pBA->bValid = true;
	if (Time != 0)
		mod_timer(&pBA->Timer, jiffies + msecs_to_jiffies(Time));
}