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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {size_t prefixSize; scalar_t__ extDictSize; int /*<<< orphan*/ * externalDict; int /*<<< orphan*/  const* prefixEnd; } ;
struct TYPE_5__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_1__ LZ4_streamDecode_t_internal ;
typedef  TYPE_2__ LZ4_streamDecode_t ;

/* Variables and functions */

int LZ4_setStreamDecode (LZ4_streamDecode_t* LZ4_streamDecode, const char* dictionary, int dictSize) {
	LZ4_streamDecode_t_internal* lz4sd = &LZ4_streamDecode->internal_donotuse;
	lz4sd->prefixSize = (size_t) dictSize;
	lz4sd->prefixEnd = (const ut8*) dictionary + dictSize;
	lz4sd->externalDict = NULL;
	lz4sd->extDictSize  = 0;
	return 1;
}