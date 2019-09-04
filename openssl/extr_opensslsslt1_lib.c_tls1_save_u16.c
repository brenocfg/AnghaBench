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
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned int*) ; 
 unsigned int* OPENSSL_malloc (size_t) ; 
 scalar_t__ PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_TLS1_SAVE_U16 ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls1_save_u16(PACKET *pkt, uint16_t **pdest, size_t *pdestlen)
{
    unsigned int stmp;
    size_t size, i;
    uint16_t *buf;

    size = PACKET_remaining(pkt);

    /* Invalid data length */
    if (size == 0 || (size & 1) != 0)
        return 0;

    size >>= 1;

    if ((buf = OPENSSL_malloc(size * sizeof(*buf))) == NULL)  {
        SSLerr(SSL_F_TLS1_SAVE_U16, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    for (i = 0; i < size && PACKET_get_net_2(pkt, &stmp); i++)
        buf[i] = stmp;

    if (i != size) {
        OPENSSL_free(buf);
        return 0;
    }

    OPENSSL_free(*pdest);
    *pdest = buf;
    *pdestlen = size;

    return 1;
}