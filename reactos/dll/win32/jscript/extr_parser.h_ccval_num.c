#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double n; } ;
struct TYPE_5__ {TYPE_1__ u; int /*<<< orphan*/  is_num; } ;
typedef  TYPE_2__ ccval_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline ccval_t ccval_num(double n)
{
    ccval_t r;
    r.is_num = TRUE;
    r.u.n = n;
    return r;
}