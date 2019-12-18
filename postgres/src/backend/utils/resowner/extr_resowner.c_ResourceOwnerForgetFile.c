#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  filearr; } ;
typedef  TYPE_1__* ResourceOwner ;
typedef  int /*<<< orphan*/  File ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FileGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceArrayRemove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ResourceOwnerForgetFile(ResourceOwner owner, File file)
{
	if (!ResourceArrayRemove(&(owner->filearr), FileGetDatum(file)))
		elog(ERROR, "temporary file %d is not owned by resource owner %s",
			 file, owner->name);
}