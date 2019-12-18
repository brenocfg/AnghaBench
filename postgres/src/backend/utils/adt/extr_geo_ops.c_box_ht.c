#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  float8 ;
struct TYPE_6__ {int /*<<< orphan*/  y; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; } ;
struct TYPE_7__ {TYPE_2__ low; TYPE_1__ high; } ;
typedef  TYPE_3__ BOX ;

/* Variables and functions */
 int /*<<< orphan*/  float8_mi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float8
box_ht(BOX *box)
{
	return float8_mi(box->high.y, box->low.y);
}