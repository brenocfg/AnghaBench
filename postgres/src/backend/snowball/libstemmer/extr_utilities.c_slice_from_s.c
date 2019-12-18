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
typedef  int /*<<< orphan*/  symbol ;
struct SN_env {int /*<<< orphan*/  ket; int /*<<< orphan*/  bra; } ;

/* Variables and functions */
 int replace_s (struct SN_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ slice_check (struct SN_env*) ; 

extern int slice_from_s(struct SN_env * z, int s_size, const symbol * s) {
    if (slice_check(z)) return -1;
    return replace_s(z, z->bra, z->ket, s_size, s, NULL);
}