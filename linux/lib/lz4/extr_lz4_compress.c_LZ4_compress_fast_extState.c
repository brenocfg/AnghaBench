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
typedef  int /*<<< orphan*/  tableType_t ;
struct TYPE_3__ {int /*<<< orphan*/  internal_donotuse; } ;
typedef  int /*<<< orphan*/  LZ4_stream_t_internal ;
typedef  TYPE_1__ LZ4_stream_t ;

/* Variables and functions */
 int LZ4_64Klimit ; 
 int LZ4_ACCELERATION_DEFAULT ; 
 int LZ4_COMPRESSBOUND (int) ; 
 int LZ4_compress_generic (int /*<<< orphan*/ *,char const*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LZ4_resetStream (TYPE_1__*) ; 
 int /*<<< orphan*/  byPtr ; 
 int /*<<< orphan*/  const byU16 ; 
 int /*<<< orphan*/  byU32 ; 
 int /*<<< orphan*/  limitedOutput ; 
 int /*<<< orphan*/  noDict ; 
 int /*<<< orphan*/  noDictIssue ; 
 int /*<<< orphan*/  noLimit ; 

__attribute__((used)) static int LZ4_compress_fast_extState(
	void *state,
	const char *source,
	char *dest,
	int inputSize,
	int maxOutputSize,
	int acceleration)
{
	LZ4_stream_t_internal *ctx = &((LZ4_stream_t *)state)->internal_donotuse;
#if LZ4_ARCH64
	const tableType_t tableType = byU32;
#else
	const tableType_t tableType = byPtr;
#endif

	LZ4_resetStream((LZ4_stream_t *)state);

	if (acceleration < 1)
		acceleration = LZ4_ACCELERATION_DEFAULT;

	if (maxOutputSize >= LZ4_COMPRESSBOUND(inputSize)) {
		if (inputSize < LZ4_64Klimit)
			return LZ4_compress_generic(ctx, source,
				dest, inputSize, 0,
				noLimit, byU16, noDict,
				noDictIssue, acceleration);
		else
			return LZ4_compress_generic(ctx, source,
				dest, inputSize, 0,
				noLimit, tableType, noDict,
				noDictIssue, acceleration);
	} else {
		if (inputSize < LZ4_64Klimit)
			return LZ4_compress_generic(ctx, source,
				dest, inputSize,
				maxOutputSize, limitedOutput, byU16, noDict,
				noDictIssue, acceleration);
		else
			return LZ4_compress_generic(ctx, source,
				dest, inputSize,
				maxOutputSize, limitedOutput, tableType, noDict,
				noDictIssue, acceleration);
	}
}