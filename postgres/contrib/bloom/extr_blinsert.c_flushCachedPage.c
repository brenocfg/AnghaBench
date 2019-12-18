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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  GenericXLogState ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_2__ BloomBuildState ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BloomNewBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_XLOG_FULL_IMAGE ; 
 int /*<<< orphan*/  GenericXLogFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenericXLogRegisterBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GenericXLogStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flushCachedPage(Relation index, BloomBuildState *buildstate)
{
	Page		page;
	Buffer		buffer = BloomNewBuffer(index);
	GenericXLogState *state;

	state = GenericXLogStart(index);
	page = GenericXLogRegisterBuffer(state, buffer, GENERIC_XLOG_FULL_IMAGE);
	memcpy(page, buildstate->data.data, BLCKSZ);
	GenericXLogFinish(state);
	UnlockReleaseBuffer(buffer);
}