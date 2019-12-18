#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cryptopro_ext ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_8__ {TYPE_2__* new_cipher; } ;
struct TYPE_10__ {TYPE_1__ tmp; } ;
struct TYPE_11__ {TYPE_3__ s3; } ;
struct TYPE_9__ {int id; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_CRYPTOPRO_BUG ; 
 int SSL_OP_CRYPTOPRO_TLSEXT_BUG ; 
 int SSL_get_options (TYPE_4__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 

EXT_RETURN tls_construct_stoc_cryptopro_bug(SSL *s, WPACKET *pkt,
                                            unsigned int context, X509 *x,
                                            size_t chainidx)
{
    const unsigned char cryptopro_ext[36] = {
        0xfd, 0xe8,         /* 65000 */
        0x00, 0x20,         /* 32 bytes length */
        0x30, 0x1e, 0x30, 0x08, 0x06, 0x06, 0x2a, 0x85,
        0x03, 0x02, 0x02, 0x09, 0x30, 0x08, 0x06, 0x06,
        0x2a, 0x85, 0x03, 0x02, 0x02, 0x16, 0x30, 0x08,
        0x06, 0x06, 0x2a, 0x85, 0x03, 0x02, 0x02, 0x17
    };

    if (((s->s3.tmp.new_cipher->id & 0xFFFF) != 0x80
         && (s->s3.tmp.new_cipher->id & 0xFFFF) != 0x81)
            || (SSL_get_options(s) & SSL_OP_CRYPTOPRO_TLSEXT_BUG) == 0)
        return EXT_RETURN_NOT_SENT;

    if (!WPACKET_memcpy(pkt, cryptopro_ext, sizeof(cryptopro_ext))) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_STOC_CRYPTOPRO_BUG, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}