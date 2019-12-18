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
typedef  scalar_t__ LZ4F_errorCode_t ;

/* Variables and functions */
 scalar_t__ LZ4F_ERROR_maxCode ; 

unsigned LZ4F_isError(LZ4F_errorCode_t code)
{
    return (code > (LZ4F_errorCode_t)(-LZ4F_ERROR_maxCode));
}