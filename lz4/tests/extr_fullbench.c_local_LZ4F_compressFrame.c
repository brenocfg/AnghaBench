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

/* Variables and functions */
 scalar_t__ LZ4F_compressFrame (char*,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4F_compressFrameBound (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int local_LZ4F_compressFrame(const char* in, char* out, int inSize)
{
    assert(inSize >= 0);
    return (int)LZ4F_compressFrame(out, LZ4F_compressFrameBound((size_t)inSize, NULL), in, (size_t)inSize, NULL);
}