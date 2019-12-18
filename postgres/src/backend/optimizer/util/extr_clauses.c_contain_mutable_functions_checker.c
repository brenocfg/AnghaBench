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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ PROVOLATILE_IMMUTABLE ; 
 scalar_t__ func_volatile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
contain_mutable_functions_checker(Oid func_id, void *context)
{
	return (func_volatile(func_id) != PROVOLATILE_IMMUTABLE);
}