#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt32 ;
struct TYPE_6__ {size_t mNumberBuffers; TYPE_1__* mBuffers; } ;
struct TYPE_5__ {TYPE_2__* mData; } ;
typedef  TYPE_2__ AudioBufferList ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_2__*) ; 

__attribute__((used)) static void buf_list_free(AudioBufferList *buf_list)
{
	if (buf_list) {
		for (UInt32 i = 0; i < buf_list->mNumberBuffers; i++)
			bfree(buf_list->mBuffers[i].mData);

		bfree(buf_list);
	}
}