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
struct runtime_stat {int dummy; } ;

/* Variables and functions */
 double sanitize_val (double) ; 
 double td_bad_spec (int,int,struct runtime_stat*) ; 
 double td_fe_bound (int,int,struct runtime_stat*) ; 
 double td_retiring (int,int,struct runtime_stat*) ; 

__attribute__((used)) static double td_be_bound(int ctx, int cpu, struct runtime_stat *st)
{
	double sum = (td_fe_bound(ctx, cpu, st) +
		      td_bad_spec(ctx, cpu, st) +
		      td_retiring(ctx, cpu, st));
	if (sum == 0)
		return 0;
	return sanitize_val(1.0 - sum);
}