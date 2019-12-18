#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  multiInsertBuffers; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ri_CopyMultiInsertBuffer; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  TYPE_2__ CopyMultiInsertInfo ;
typedef  int /*<<< orphan*/  CopyMultiInsertBuffer ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyMultiInsertBufferInit (TYPE_1__*) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
CopyMultiInsertInfoSetupBuffer(CopyMultiInsertInfo *miinfo,
							   ResultRelInfo *rri)
{
	CopyMultiInsertBuffer *buffer;

	buffer = CopyMultiInsertBufferInit(rri);

	/* Setup back-link so we can easily find this buffer again */
	rri->ri_CopyMultiInsertBuffer = buffer;
	/* Record that we're tracking this buffer */
	miinfo->multiInsertBuffers = lappend(miinfo->multiInsertBuffers, buffer);
}