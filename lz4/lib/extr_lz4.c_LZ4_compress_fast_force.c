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
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_3__ {int /*<<< orphan*/  internal_donotuse; } ;
typedef  TYPE_1__ LZ4_stream_t ;

/* Variables and functions */
 int LZ4_64Klimit ; 
 int LZ4_compress_generic (int /*<<< orphan*/ *,char const*,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LZ4_initStream (TYPE_1__*,int) ; 
 int /*<<< orphan*/  byPtr ; 
 int /*<<< orphan*/  const byU16 ; 
 int /*<<< orphan*/  byU32 ; 
 int /*<<< orphan*/  limitedOutput ; 
 int /*<<< orphan*/  noDict ; 
 int /*<<< orphan*/  noDictIssue ; 

int LZ4_compress_fast_force(const char* src, char* dst, int srcSize, int dstCapacity, int acceleration)
{
    LZ4_stream_t ctx;
    LZ4_initStream(&ctx, sizeof(ctx));

    if (srcSize < LZ4_64Klimit) {
        return LZ4_compress_generic(&ctx.internal_donotuse, src, dst, srcSize, NULL, dstCapacity, limitedOutput, byU16,    noDict, noDictIssue, acceleration);
    } else {
        tableType_t const addrMode = (sizeof(void*) > 4) ? byU32 : byPtr;
        return LZ4_compress_generic(&ctx.internal_donotuse, src, dst, srcSize, NULL, dstCapacity, limitedOutput, addrMode, noDict, noDictIssue, acceleration);
    }
}