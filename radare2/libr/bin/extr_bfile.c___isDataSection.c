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
struct TYPE_3__ {int /*<<< orphan*/  name; scalar_t__ is_data; scalar_t__ has_strings; } ;
typedef  TYPE_1__ RBinSection ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool __isDataSection(RBinFile *a, RBinSection *s) {
	if (s->has_strings || s->is_data) {
		return true;
	}
 	// Rust
	return strstr (s->name, "_const") != NULL;
}