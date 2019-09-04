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
struct xt_hashlimit_htable {int dummy; } ;
struct dsthash_ent {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool select_all(const struct xt_hashlimit_htable *ht,
		       const struct dsthash_ent *he)
{
	return true;
}