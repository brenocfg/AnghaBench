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
struct TYPE_3__ {scalar_t__ windowLog; scalar_t__ chainLog; scalar_t__ hashLog; scalar_t__ searchLog; scalar_t__ searchLength; scalar_t__ targetLength; scalar_t__ strategy; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_CHAINLOG_MAX ; 
 scalar_t__ ZSTD_CHAINLOG_MIN ; 
 scalar_t__ ZSTD_HASHLOG_MAX ; 
 scalar_t__ ZSTD_HASHLOG_MIN ; 
 scalar_t__ ZSTD_SEARCHLENGTH_MAX ; 
 scalar_t__ ZSTD_SEARCHLENGTH_MIN ; 
 scalar_t__ ZSTD_SEARCHLOG_MAX ; 
 scalar_t__ ZSTD_SEARCHLOG_MIN ; 
 scalar_t__ ZSTD_TARGETLENGTH_MAX ; 
 scalar_t__ ZSTD_TARGETLENGTH_MIN ; 
 scalar_t__ ZSTD_WINDOWLOG_MAX ; 
 scalar_t__ ZSTD_WINDOWLOG_MIN ; 
 scalar_t__ ZSTD_btopt2 ; 
 int /*<<< orphan*/  compressionParameter_unsupported ; 

size_t ZSTD_checkCParams(ZSTD_compressionParameters cParams)
{
#define CLAMPCHECK(val, min, max)                                       \
	{                                                               \
		if ((val < min) | (val > max))                          \
			return ERROR(compressionParameter_unsupported); \
	}
	CLAMPCHECK(cParams.windowLog, ZSTD_WINDOWLOG_MIN, ZSTD_WINDOWLOG_MAX);
	CLAMPCHECK(cParams.chainLog, ZSTD_CHAINLOG_MIN, ZSTD_CHAINLOG_MAX);
	CLAMPCHECK(cParams.hashLog, ZSTD_HASHLOG_MIN, ZSTD_HASHLOG_MAX);
	CLAMPCHECK(cParams.searchLog, ZSTD_SEARCHLOG_MIN, ZSTD_SEARCHLOG_MAX);
	CLAMPCHECK(cParams.searchLength, ZSTD_SEARCHLENGTH_MIN, ZSTD_SEARCHLENGTH_MAX);
	CLAMPCHECK(cParams.targetLength, ZSTD_TARGETLENGTH_MIN, ZSTD_TARGETLENGTH_MAX);
	if ((U32)(cParams.strategy) > (U32)ZSTD_btopt2)
		return ERROR(compressionParameter_unsupported);
	return 0;
}