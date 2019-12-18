#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  rightlink; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  GinPageOpaqueData ;
typedef  TYPE_1__* GinPageOpaque ;

/* Variables and functions */
 TYPE_1__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  PageInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
GinInitPage(Page page, uint32 f, Size pageSize)
{
	GinPageOpaque opaque;

	PageInit(page, pageSize, sizeof(GinPageOpaqueData));

	opaque = GinPageGetOpaque(page);
	memset(opaque, 0, sizeof(GinPageOpaqueData));
	opaque->flags = f;
	opaque->rightlink = InvalidBlockNumber;
}