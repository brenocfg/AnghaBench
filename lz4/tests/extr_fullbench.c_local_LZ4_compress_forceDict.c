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
 int LZ4_compress_forceExtDict (int /*<<< orphan*/ *,char const*,char*,int) ; 
 int /*<<< orphan*/  LZ4_stream ; 

__attribute__((used)) static int local_LZ4_compress_forceDict(const char* in, char* out, int inSize)
{
    return LZ4_compress_forceExtDict(&LZ4_stream, in, out, inSize);
}