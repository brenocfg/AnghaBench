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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ bf_key ;

/* Variables and functions */
 int /*<<< orphan*/  BF_ENC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BF_ROUNDS ; 

__attribute__((used)) static void bf_enc(uint32_t *x, bf_key *key)
{
    uint32_t  Xl;
    uint32_t  Xr;
    uint32_t  temp;
    int	i;

    Xl = x[0];
    Xr = x[1];

    for (i = 0; i < BF_ROUNDS; ++i)
    {
        Xl ^= key->p[i];
        Xr ^= BF_ENC(Xl,key->s);

        temp = Xl;
        Xl = Xr;
        Xr = temp;
    }

    Xl ^= key->p[BF_ROUNDS];
    Xr ^= key->p[BF_ROUNDS + 1];

    x[0] = Xr;
    x[1] = Xl;
}