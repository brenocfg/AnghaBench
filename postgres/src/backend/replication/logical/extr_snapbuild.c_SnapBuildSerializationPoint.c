#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_1__ SnapBuild ;

/* Variables and functions */
 scalar_t__ SNAPBUILD_CONSISTENT ; 
 int /*<<< orphan*/  SnapBuildRestore (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapBuildSerialize (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
SnapBuildSerializationPoint(SnapBuild *builder, XLogRecPtr lsn)
{
	if (builder->state < SNAPBUILD_CONSISTENT)
		SnapBuildRestore(builder, lsn);
	else
		SnapBuildSerialize(builder, lsn);
}