#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t pos; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ WordEntryIN ;

/* Variables and functions */
 int tsCompareString (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
compareentry(const void *va, const void *vb, void *arg)
{
	const WordEntryIN *a = (const WordEntryIN *) va;
	const WordEntryIN *b = (const WordEntryIN *) vb;
	char	   *BufferStr = (char *) arg;

	return tsCompareString(&BufferStr[a->entry.pos], a->entry.len,
						   &BufferStr[b->entry.pos], b->entry.len,
						   false);
}