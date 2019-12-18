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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nfs_opnum_to_string (scalar_t__) ; 

__attribute__((used)) static __inline int unexpected_op(uint32_t op, uint32_t expected)
{
    if (op == expected)
        return 0;

    eprintf("Op table mismatch. Got %s (%d), expected %s (%d).\n",
        nfs_opnum_to_string(op), op,
        nfs_opnum_to_string(expected), expected);
    return 1;
}