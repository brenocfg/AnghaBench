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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  RELOPT_KIND_BTREE ; 
 int /*<<< orphan*/ * default_reloptions (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bytea *
btoptions(Datum reloptions, bool validate)
{
	return default_reloptions(reloptions, validate, RELOPT_KIND_BTREE);
}