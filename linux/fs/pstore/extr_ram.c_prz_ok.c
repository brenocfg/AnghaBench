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
struct persistent_ram_zone {int dummy; } ;

/* Variables and functions */
 scalar_t__ persistent_ram_ecc_string (struct persistent_ram_zone*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ persistent_ram_old_size (struct persistent_ram_zone*) ; 

__attribute__((used)) static bool prz_ok(struct persistent_ram_zone *prz)
{
	return !!prz && !!(persistent_ram_old_size(prz) +
			   persistent_ram_ecc_string(prz, NULL, 0));
}