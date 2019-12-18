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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  address_direct (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool singlearg_direct(ut8 const firstbyte, char const* arg
	, ut8 **out)
{
	ut8 address;
	if (!address_direct (arg, &address)) {
		return false;
	}
	(*out)[0] = firstbyte;
	(*out)[1] = address;
	*out += 2;
	return true;
}