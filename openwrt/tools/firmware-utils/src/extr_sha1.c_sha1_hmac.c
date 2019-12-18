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
typedef  int uint ;
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sha1_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha1_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha1_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void sha1_hmac( uchar *key, uint keylen, uchar *buf, uint buflen,
                uchar digest[20] )
{
    uint i;
    sha1_context ctx;
    uchar k_ipad[64];
    uchar k_opad[64];
    uchar tmpbuf[20];

    memset( k_ipad, 0x36, 64 );
    memset( k_opad, 0x5C, 64 );

    for( i = 0; i < keylen; i++ )
    {
        if( i >= 64 ) break;

        k_ipad[i] ^= key[i];
        k_opad[i] ^= key[i];
    }

    sha1_starts( &ctx );
    sha1_update( &ctx, k_ipad, 64 );
    sha1_update( &ctx, buf, buflen );
    sha1_finish( &ctx, tmpbuf );

    sha1_starts( &ctx );
    sha1_update( &ctx, k_opad, 64 );
    sha1_update( &ctx, tmpbuf, 20 );
    sha1_finish( &ctx, digest );

    memset( k_ipad, 0, 64 );
    memset( k_opad, 0, 64 );
    memset( tmpbuf, 0, 20 );
    memset( &ctx, 0, sizeof( sha1_context ) );
}