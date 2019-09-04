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
typedef  int /*<<< orphan*/  widefelem ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_diff_128_64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void felem_neg(felem out, const felem in)
{
    widefelem tmp;

    memset(tmp, 0, sizeof(tmp));
    felem_diff_128_64(tmp, in);
    felem_reduce(out, tmp);
}