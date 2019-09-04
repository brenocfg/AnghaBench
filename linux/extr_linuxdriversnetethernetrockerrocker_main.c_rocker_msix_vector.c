#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rocker {TYPE_1__* msix_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */

__attribute__((used)) static u32 rocker_msix_vector(const struct rocker *rocker, unsigned int vector)
{
	return rocker->msix_entries[vector].vector;
}