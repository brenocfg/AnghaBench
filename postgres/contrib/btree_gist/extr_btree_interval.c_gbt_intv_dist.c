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
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  Interval ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Abs (scalar_t__) ; 
 scalar_t__ intr2num (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static float8
gbt_intv_dist(const void *a, const void *b, FmgrInfo *flinfo)
{
	return (float8) Abs(intr2num((const Interval *) a) - intr2num((const Interval *) b));
}