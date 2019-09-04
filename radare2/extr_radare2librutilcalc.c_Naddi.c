#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_4__ {double d; int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ RNumCalcValue ;

/* Variables and functions */

__attribute__((used)) static inline RNumCalcValue Naddi(RNumCalcValue n, ut64 v) { n.d += (double)v; n.n += v; return n; }