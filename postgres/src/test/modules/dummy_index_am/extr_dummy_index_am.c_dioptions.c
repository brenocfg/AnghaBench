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
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  DummyIndexOptions ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ build_reloptions (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_relopt_kind ; 
 int /*<<< orphan*/  di_relopt_tab ; 
 int /*<<< orphan*/  lengthof (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bytea *
dioptions(Datum reloptions, bool validate)
{
	return (bytea *) build_reloptions(reloptions, validate,
									  di_relopt_kind,
									  sizeof(DummyIndexOptions),
									  di_relopt_tab, lengthof(di_relopt_tab));
}