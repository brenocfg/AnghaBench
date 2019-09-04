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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  fe ;

/* Variables and functions */
 int /*<<< orphan*/  fe_tobytes (int*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int fe_isnegative(const fe f)
{
    uint8_t s[32];

    fe_tobytes(s, f);
    return s[0] & 1;
}