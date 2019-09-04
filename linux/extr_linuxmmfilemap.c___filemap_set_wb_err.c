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
struct address_space {int /*<<< orphan*/  wb_err; } ;
typedef  int /*<<< orphan*/  errseq_t ;

/* Variables and functions */
 int /*<<< orphan*/  errseq_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_filemap_set_wb_err (struct address_space*,int /*<<< orphan*/ ) ; 

void __filemap_set_wb_err(struct address_space *mapping, int err)
{
	errseq_t eseq = errseq_set(&mapping->wb_err, err);

	trace_filemap_set_wb_err(mapping, eseq);
}