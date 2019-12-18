#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct r_bin_mz_obj_t {TYPE_1__* dos_header; } ;
struct TYPE_2__ {int header_paragraphs; } ;

/* Variables and functions */

__attribute__((used)) static ut64 r_bin_mz_la_to_pa(const struct r_bin_mz_obj_t *bin, ut64 la) {
	return la + (bin->dos_header->header_paragraphs << 4);
}