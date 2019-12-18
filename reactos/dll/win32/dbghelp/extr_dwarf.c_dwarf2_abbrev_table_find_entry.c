#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sparse_array {int dummy; } ;
typedef  int /*<<< orphan*/  dwarf2_abbrev_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sparse_array_find (struct sparse_array const*,unsigned long) ; 

__attribute__((used)) static dwarf2_abbrev_entry_t*
dwarf2_abbrev_table_find_entry(const struct sparse_array* abbrev_table,
                               unsigned long entry_code)
{
    assert( NULL != abbrev_table );
    return sparse_array_find(abbrev_table, entry_code);
}