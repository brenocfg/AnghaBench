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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int GET_USHORT (int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static inline unsigned GET_UINT(const BYTE* buffer, unsigned i)
{
    return GET_USHORT(buffer, i) + 0x10000 * GET_USHORT(buffer, i + 2);
}