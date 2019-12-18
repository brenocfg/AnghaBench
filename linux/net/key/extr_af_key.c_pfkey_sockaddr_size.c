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
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int PFKEY_ALIGN8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_sockaddr_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfkey_sockaddr_size(sa_family_t family)
{
	return PFKEY_ALIGN8(pfkey_sockaddr_len(family));
}