#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct posix_ace_state_array {int n; TYPE_1__* aces; } ;
struct TYPE_2__ {int /*<<< orphan*/  perms; } ;

/* Variables and functions */
 int /*<<< orphan*/  deny_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void deny_bits_array(struct posix_ace_state_array *a, u32 mask)
{
	int i;

	for (i=0; i < a->n; i++)
		deny_bits(&a->aces[i].perms, mask);
}