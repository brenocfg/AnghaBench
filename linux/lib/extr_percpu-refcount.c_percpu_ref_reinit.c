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
struct percpu_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  percpu_ref_is_zero (struct percpu_ref*) ; 
 int /*<<< orphan*/  percpu_ref_resurrect (struct percpu_ref*) ; 

void percpu_ref_reinit(struct percpu_ref *ref)
{
	WARN_ON_ONCE(!percpu_ref_is_zero(ref));

	percpu_ref_resurrect(ref);
}