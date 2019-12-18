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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {int /*<<< orphan*/ * bufferStart; } ;
struct TYPE_6__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_2__ LZ4_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void LZ4_init(LZ4_stream_t* lz4ds, ut8* base) {
	memset (lz4ds, 0, sizeof(LZ4_stream_t));
	lz4ds->internal_donotuse.bufferStart = base;
}