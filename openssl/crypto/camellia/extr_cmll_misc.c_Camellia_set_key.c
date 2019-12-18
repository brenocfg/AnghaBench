#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rd_key; } ;
struct TYPE_5__ {TYPE_1__ u; int /*<<< orphan*/  grand_rounds; } ;
typedef  TYPE_2__ CAMELLIA_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  Camellia_Ekeygen (int const,unsigned char const*,int /*<<< orphan*/ ) ; 

int Camellia_set_key(const unsigned char *userKey, const int bits,
                     CAMELLIA_KEY *key)
{
    if (!userKey || !key)
        return -1;
    if (bits != 128 && bits != 192 && bits != 256)
        return -2;
    key->grand_rounds = Camellia_Ekeygen(bits, userKey, key->u.rd_key);
    return 0;
}