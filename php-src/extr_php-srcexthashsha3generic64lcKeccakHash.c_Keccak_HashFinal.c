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
struct TYPE_3__ {int fixedOutputLength; int /*<<< orphan*/  sponge; int /*<<< orphan*/  delimitedSuffix; } ;
typedef  TYPE_1__ Keccak_HashInstance ;
typedef  scalar_t__ HashReturn ;
typedef  int /*<<< orphan*/  BitSequence ;

/* Variables and functions */
 int /*<<< orphan*/  KeccakWidth1600_SpongeAbsorbLastFewBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeccakWidth1600_SpongeSqueeze (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SUCCESS ; 

HashReturn Keccak_HashFinal(Keccak_HashInstance *instance, BitSequence *hashval)
{
    HashReturn ret = (HashReturn)KeccakWidth1600_SpongeAbsorbLastFewBits(&instance->sponge, instance->delimitedSuffix);
    if (ret == SUCCESS)
        return (HashReturn)KeccakWidth1600_SpongeSqueeze(&instance->sponge, hashval, instance->fixedOutputLength/8);
    else
        return ret;
}