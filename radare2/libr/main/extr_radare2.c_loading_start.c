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
 int /*<<< orphan*/  loading_thread ; 
 int /*<<< orphan*/  r_th_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_th_setname (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ r_th_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread ; 

__attribute__((used)) static void loading_start() {
	thread = r_th_new (loading_thread, NULL, 1);
	if (r_th_start (thread, true)) {
		r_th_setname (thread, "r2_th");
	}
}