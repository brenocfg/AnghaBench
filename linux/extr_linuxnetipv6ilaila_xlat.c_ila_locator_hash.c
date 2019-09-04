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
typedef  int /*<<< orphan*/  u32 ;
struct ila_locator {scalar_t__ v32; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ila_hash_secret_init () ; 
 int /*<<< orphan*/  hashrnd ; 
 int /*<<< orphan*/  jhash_2words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ila_locator_hash(struct ila_locator loc)
{
	u32 *v = (u32 *)loc.v32;

	__ila_hash_secret_init();
	return jhash_2words(v[0], v[1], hashrnd);
}