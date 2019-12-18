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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  key_serial_t ;

/* Variables and functions */
 long EOPNOTSUPP ; 

__attribute__((used)) static inline long keyctl_get_persistent(uid_t uid, key_serial_t destring)
{
	return -EOPNOTSUPP;
}