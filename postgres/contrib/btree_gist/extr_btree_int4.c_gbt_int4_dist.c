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
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FLOAT_DISTANCE (int /*<<< orphan*/ ,void const*,void const*) ; 
 int /*<<< orphan*/  int32 ; 

__attribute__((used)) static float8
gbt_int4_dist(const void *a, const void *b, FmgrInfo *flinfo)
{
	return GET_FLOAT_DISTANCE(int32, a, b);
}