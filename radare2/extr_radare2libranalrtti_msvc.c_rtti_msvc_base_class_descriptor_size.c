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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_3__ {scalar_t__ word_size; } ;
typedef  TYPE_1__ RVTableContext ;

/* Variables and functions */

__attribute__((used)) static ut64 rtti_msvc_base_class_descriptor_size(RVTableContext *context) {
	return context->word_size + 5 * sizeof (ut32);
}