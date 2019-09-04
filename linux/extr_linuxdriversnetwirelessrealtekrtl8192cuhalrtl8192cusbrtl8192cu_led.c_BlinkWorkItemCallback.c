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
struct work_struct {int dummy; } ;
typedef  int /*<<< orphan*/  PLED_871x ;

/* Variables and functions */
 int /*<<< orphan*/  BlinkHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BlinkWorkItem ; 
 int /*<<< orphan*/  LED_871x ; 
 int /*<<< orphan*/  container_of (struct work_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BlinkWorkItemCallback(struct work_struct *work)
{
	PLED_871x	 pLed = container_of(work, LED_871x, BlinkWorkItem);
	BlinkHandler(pLed);
}