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
struct TYPE_4__ {int /*<<< orphan*/  hmac; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  RAND_DRBG_HMAC ;
typedef  TYPE_2__ RAND_DRBG ;

/* Variables and functions */
 int do_hmac (int /*<<< orphan*/ *,int,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t) ; 

__attribute__((used)) static int drbg_hmac_update(RAND_DRBG *drbg,
                            const unsigned char *in1, size_t in1len,
                            const unsigned char *in2, size_t in2len,
                            const unsigned char *in3, size_t in3len)
{
    RAND_DRBG_HMAC *hmac = &drbg->data.hmac;

    /* (Steps 1-2) K = HMAC(K, V||0x00||provided_data). V = HMAC(K,V) */
    if (!do_hmac(hmac, 0x00, in1, in1len, in2, in2len, in3, in3len))
        return 0;
    /* (Step 3) If provided_data == NULL then return (K,V) */
    if (in1len == 0 && in2len == 0 && in3len == 0)
        return 1;
    /* (Steps 4-5) K = HMAC(K, V||0x01||provided_data). V = HMAC(K,V) */
    return do_hmac(hmac, 0x01, in1, in1len, in2, in2len, in3, in3len);
}