#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  float8 ;
struct TYPE_3__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ LSEG ;

/* Variables and functions */
 int /*<<< orphan*/  point_invsl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline float8
lseg_invsl(LSEG *lseg)
{
	return point_invsl(&lseg->p[0], &lseg->p[1]);
}