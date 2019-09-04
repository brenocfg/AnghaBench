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
 int /*<<< orphan*/  static_key_disable (struct static_key*) ; 
 int /*<<< orphan*/  static_key_enable (struct static_key*) ; 
 scalar_t__ static_key_enabled (struct static_key*) ; 

__attribute__((used)) static void invert_key(struct static_key *key)
{
	if (static_key_enabled(key))
		static_key_disable(key);
	else
		static_key_enable(key);
}