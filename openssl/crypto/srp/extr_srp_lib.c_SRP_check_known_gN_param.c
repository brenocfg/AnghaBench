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
struct TYPE_2__ {char* id; int /*<<< orphan*/  N; int /*<<< orphan*/  g; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 size_t KNOWN_GN_NUMBER ; 
 TYPE_1__* knowngN ; 

char *SRP_check_known_gN_param(const BIGNUM *g, const BIGNUM *N)
{
    size_t i;
    if ((g == NULL) || (N == NULL))
        return NULL;

    for (i = 0; i < KNOWN_GN_NUMBER; i++) {
        if (BN_cmp(knowngN[i].g, g) == 0 && BN_cmp(knowngN[i].N, N) == 0)
            return knowngN[i].id;
    }
    return NULL;
}