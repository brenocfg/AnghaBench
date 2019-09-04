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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ RTLLIB_STYPE_BEACON ; 
 scalar_t__ WLAN_FC_GET_STYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_beacon(u16 fc)
{
	return (WLAN_FC_GET_STYPE(fc) == RTLLIB_STYPE_BEACON);
}