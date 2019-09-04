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
struct qm_ecir2 {int info; } ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static bool qm_ecir2_is_dcp(const struct qm_ecir2 *p)
{
	return p->info & BIT(31);
}