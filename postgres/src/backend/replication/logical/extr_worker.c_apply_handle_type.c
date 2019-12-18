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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  LogicalRepTyp ;

/* Variables and functions */
 int /*<<< orphan*/  logicalrep_read_typ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logicalrep_typmap_update (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
apply_handle_type(StringInfo s)
{
	LogicalRepTyp typ;

	logicalrep_read_typ(s, &typ);
	logicalrep_typmap_update(&typ);
}