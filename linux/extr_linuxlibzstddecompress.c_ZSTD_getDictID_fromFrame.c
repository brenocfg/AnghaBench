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
struct TYPE_3__ {int dictID; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ZSTD_frameParams ;

/* Variables and functions */
 size_t ZSTD_getFrameParams (TYPE_1__*,void const*,size_t) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 

unsigned ZSTD_getDictID_fromFrame(const void *src, size_t srcSize)
{
	ZSTD_frameParams zfp = {0, 0, 0, 0};
	size_t const hError = ZSTD_getFrameParams(&zfp, src, srcSize);
	if (ZSTD_isError(hError))
		return 0;
	return zfp.dictID;
}