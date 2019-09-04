#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* d1; } ;
struct TYPE_6__ {size_t mtu; } ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 size_t DTLS1_RT_HEADER_LENGTH ; 
 scalar_t__ SSL_READ_ETM (TYPE_2__ const*) ; 
 int /*<<< orphan*/ * SSL_get_current_cipher (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ssl_cipher_get_overhead (int /*<<< orphan*/  const*,size_t*,size_t*,size_t*,size_t*) ; 

size_t DTLS_get_data_mtu(const SSL *s)
{
    size_t mac_overhead, int_overhead, blocksize, ext_overhead;
    const SSL_CIPHER *ciph = SSL_get_current_cipher(s);
    size_t mtu = s->d1->mtu;

    if (ciph == NULL)
        return 0;

    if (!ssl_cipher_get_overhead(ciph, &mac_overhead, &int_overhead,
                                 &blocksize, &ext_overhead))
        return 0;

    if (SSL_READ_ETM(s))
        ext_overhead += mac_overhead;
    else
        int_overhead += mac_overhead;

    /* Subtract external overhead (e.g. IV/nonce, separate MAC) */
    if (ext_overhead + DTLS1_RT_HEADER_LENGTH >= mtu)
        return 0;
    mtu -= ext_overhead + DTLS1_RT_HEADER_LENGTH;

    /* Round encrypted payload down to cipher block size (for CBC etc.)
     * No check for overflow since 'mtu % blocksize' cannot exceed mtu. */
    if (blocksize)
        mtu -= (mtu % blocksize);

    /* Subtract internal overhead (e.g. CBC padding len byte) */
    if (int_overhead >= mtu)
        return 0;
    mtu -= int_overhead;

    return mtu;
}