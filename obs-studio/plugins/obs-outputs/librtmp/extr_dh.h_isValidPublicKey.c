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
typedef  int /*<<< orphan*/  MP_t ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ MP_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MP_cmp_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_modexp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_set_w (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MP_sub_w (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTMP_LOGERROR ; 
 int /*<<< orphan*/  RTMP_LOGWARNING ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isValidPublicKey(MP_t y, MP_t p, MP_t q)
{
    int ret = TRUE;
    MP_t bn;
    assert(y);

    MP_new(bn);
    assert(bn);

    /* y must lie in [2,p-1] */
    MP_set_w(bn, 1);
    if (MP_cmp(y, bn) < 0)
    {
        RTMP_Log(RTMP_LOGERROR, "DH public key must be at least 2");
        ret = FALSE;
        goto failed;
    }

    /* bn = p-2 */
    MP_set(bn, p);
    MP_sub_w(bn, 1);
    if (MP_cmp(y, bn) > 0)
    {
        RTMP_Log(RTMP_LOGERROR, "DH public key must be at most p-2");
        ret = FALSE;
        goto failed;
    }

    /* Verify with Sophie-Germain prime
     *
     * This is a nice test to make sure the public key position is calculated
     * correctly. This test will fail in about 50% of the cases if applied to
     * random data.
     */
    if (q)
    {
        /* y must fulfill y^q mod p = 1 */
        MP_modexp(bn, y, q, p);

        if (MP_cmp_1(bn) != 0)
        {
            RTMP_Log(RTMP_LOGWARNING, "DH public key does not fulfill y^q mod p = 1");
        }
    }

failed:
    MP_free(bn);
    return ret;
}