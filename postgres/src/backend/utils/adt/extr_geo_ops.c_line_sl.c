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
typedef  double float8 ;
struct TYPE_3__ {int /*<<< orphan*/  B; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ LINE ;

/* Variables and functions */
 double DBL_MAX ; 
 scalar_t__ FPzero (int /*<<< orphan*/ ) ; 
 double float8_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline float8
line_sl(LINE *line)
{
	if (FPzero(line->A))
		return 0.0;
	if (FPzero(line->B))
		return DBL_MAX;
	return float8_div(line->A, -line->B);
}