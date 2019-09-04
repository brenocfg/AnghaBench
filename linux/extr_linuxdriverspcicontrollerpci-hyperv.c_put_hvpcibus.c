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
struct hv_pcibus_device {int /*<<< orphan*/  remove_event; int /*<<< orphan*/  remove_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_hvpcibus(struct hv_pcibus_device *hbus)
{
	if (refcount_dec_and_test(&hbus->remove_lock))
		complete(&hbus->remove_event);
}