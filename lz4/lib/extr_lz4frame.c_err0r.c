#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  scalar_t__ LZ4F_errorCodes ;
typedef  int /*<<< orphan*/  LZ4F_errorCode_t ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4F_STATIC_ASSERT (int) ; 

__attribute__((used)) static LZ4F_errorCode_t err0r(LZ4F_errorCodes code)
{
    /* A compilation error here means sizeof(ptrdiff_t) is not large enough */
    LZ4F_STATIC_ASSERT(sizeof(ptrdiff_t) >= sizeof(size_t));
    return (LZ4F_errorCode_t)-(ptrdiff_t)code;
}