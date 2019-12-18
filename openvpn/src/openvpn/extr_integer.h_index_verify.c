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
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int,int,char const*,int) ; 

__attribute__((used)) static inline int
index_verify(int index, int size, const char *file, int line)
{
    if (index < 0 || index >= size)
    {
        msg(M_FATAL, "Assertion Failed: Array index=%d out of bounds for array size=%d in %s:%d",
            index,
            size,
            file,
            line);
    }
    return index;
}