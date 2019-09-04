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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  get_address1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_address2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_address3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_from_ds (int /*<<< orphan*/ *) ; 
 int get_to_ds (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void get_BSSID(u8 *data, u8 *bssid)
{
	if (get_from_ds(data) == 1)
		get_address2(data, bssid);
	else if (get_to_ds(data) == 1)
		get_address1(data, bssid);
	else
		get_address3(data, bssid);
}