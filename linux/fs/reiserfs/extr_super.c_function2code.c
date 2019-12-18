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
typedef  scalar_t__ hashf_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int R5_HASH ; 
 int TEA_HASH ; 
 int YURA_HASH ; 
 scalar_t__ keyed_hash ; 
 scalar_t__ r5_hash ; 
 scalar_t__ yura_hash ; 

__attribute__((used)) static int function2code(hashf_t func)
{
	if (func == keyed_hash)
		return TEA_HASH;
	if (func == yura_hash)
		return YURA_HASH;
	if (func == r5_hash)
		return R5_HASH;

	BUG();			/* should never happen */

	return 0;
}