#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_8__ {TYPE_3__* ropt; } ;
struct TYPE_11__ {TYPE_1__ public; } ;
struct TYPE_10__ {int /*<<< orphan*/  use_setsessauth; scalar_t__ noOwner; } ;
typedef  TYPE_3__ RestoreOptions ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  _becomeUser (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_becomeOwner(ArchiveHandle *AH, TocEntry *te)
{
	RestoreOptions *ropt = AH->public.ropt;

	if (ropt && (ropt->noOwner || !ropt->use_setsessauth))
		return;

	_becomeUser(AH, te->owner);
}