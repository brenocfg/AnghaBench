#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/ * MP_t ;
typedef  TYPE_1__ MDH ;

/* Variables and functions */
 int /*<<< orphan*/  MDH_generate_key (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_gethex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  Q1024 ; 
 int /*<<< orphan*/  assert (size_t) ; 
 size_t isValidPublicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
DHGenerateKey(MDH *dh)
{
    size_t res = 0;
    if (!dh)
        return 0;

    while (!res)
    {
        MP_t q1 = NULL;

        if (!MDH_generate_key(dh))
            return 0;

        MP_gethex(q1, Q1024, res);
        assert(res);

        res = isValidPublicKey(dh->pub_key, dh->p, q1);
        if (!res)
        {
            MP_free(dh->pub_key);
            MP_free(dh->priv_key);
            dh->pub_key = dh->priv_key = 0;
        }

        MP_free(q1);
    }
    return 1;
}