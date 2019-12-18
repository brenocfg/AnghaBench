#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int /*<<< orphan*/  was_xmax; } ;
struct TYPE_5__ {TYPE_1__ was_running; } ;
typedef  TYPE_2__ SnapBuild ;

/* Variables and functions */

__attribute__((used)) static inline TransactionId
SnapBuildNextPhaseAt(SnapBuild *builder)
{
	/*
	 * For backward compatibility reasons this has to be stored in the wrongly
	 * named field.  Will be fixed in next major version.
	 */
	return builder->was_running.was_xmax;
}