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
typedef  int /*<<< orphan*/  LZ4F_preferences_t ;

/* Variables and functions */
 size_t LZ4F_compressBound_internal (size_t,int /*<<< orphan*/  const*,size_t) ; 

size_t LZ4F_compressBound(size_t srcSize, const LZ4F_preferences_t* preferencesPtr)
{
    return LZ4F_compressBound_internal(srcSize, preferencesPtr, (size_t)-1);
}