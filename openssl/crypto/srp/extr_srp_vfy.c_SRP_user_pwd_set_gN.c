#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const* g; int /*<<< orphan*/  const* N; } ;
typedef  TYPE_1__ SRP_user_pwd ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */

void SRP_user_pwd_set_gN(SRP_user_pwd *vinfo, const BIGNUM *g,
                         const BIGNUM *N)
{
    vinfo->N = N;
    vinfo->g = g;
}