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
struct TYPE_5__ {int /*<<< orphan*/ * sign; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque; } ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* BloomScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

void
blendscan(IndexScanDesc scan)
{
	BloomScanOpaque so = (BloomScanOpaque) scan->opaque;

	if (so->sign)
		pfree(so->sign);
	so->sign = NULL;
}