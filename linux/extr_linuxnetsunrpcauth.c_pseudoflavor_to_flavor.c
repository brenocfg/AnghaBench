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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_GSS ; 
 scalar_t__ RPC_AUTH_MAXFLAVOR ; 

__attribute__((used)) static u32
pseudoflavor_to_flavor(u32 flavor) {
	if (flavor > RPC_AUTH_MAXFLAVOR)
		return RPC_AUTH_GSS;
	return flavor;
}