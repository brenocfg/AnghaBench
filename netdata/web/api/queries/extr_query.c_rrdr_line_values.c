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
typedef  int /*<<< orphan*/  calculated_number ;
struct TYPE_3__ {long d; int /*<<< orphan*/ * v; } ;
typedef  TYPE_1__ RRDR ;

/* Variables and functions */

__attribute__((used)) static inline calculated_number *rrdr_line_values(RRDR *r, long rrdr_line) {
    return &r->v[ rrdr_line * r->d ];
}