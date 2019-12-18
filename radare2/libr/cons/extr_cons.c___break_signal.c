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
 int /*<<< orphan*/  r_cons_context_break (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_context_default ; 

__attribute__((used)) static void __break_signal(int sig) {
	r_cons_context_break (&r_cons_context_default);
}