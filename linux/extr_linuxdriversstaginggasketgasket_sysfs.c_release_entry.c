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
struct kref {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void release_entry(struct kref *ref)
{
	/* All work is done after the return from kref_put. */
}