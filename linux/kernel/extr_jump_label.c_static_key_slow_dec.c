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
struct static_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATIC_KEY_CHECK_USE (struct static_key*) ; 
 int /*<<< orphan*/  __static_key_slow_dec (struct static_key*) ; 

void static_key_slow_dec(struct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);
	__static_key_slow_dec(key);
}