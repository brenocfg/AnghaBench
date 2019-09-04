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
struct TYPE_4__ {int length; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ RBinString ;

/* Variables and functions */
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bs_cmp(const RBinString *a, const RBinString *b) {
	int diff = a->length - b->length;
	return diff == 0? strncmp (a->string, b->string, a->length): diff;
}