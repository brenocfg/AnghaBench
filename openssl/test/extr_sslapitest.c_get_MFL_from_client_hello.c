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
typedef  int /*<<< orphan*/  pkt3 ;
typedef  int /*<<< orphan*/  pkt2 ;
typedef  int /*<<< orphan*/  pkt ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ CLIENT_VERSION_LEN ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char*,long) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL3_HM_HEADER_LENGTH ; 
 scalar_t__ SSL3_RANDOM_SIZE ; 
 scalar_t__ SSL3_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_gt (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_ne (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int TLSEXT_TYPE_max_fragment_length ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_MFL_from_client_hello(BIO *bio, int *mfl_codemfl_code)
{
    long len;
    unsigned char *data;
    PACKET pkt, pkt2, pkt3;
    unsigned int MFL_code = 0, type = 0;

    if (!TEST_uint_gt( len = BIO_get_mem_data( bio, (char **) &data ), 0 ) )
        goto end;

    memset(&pkt, 0, sizeof(pkt));
    memset(&pkt2, 0, sizeof(pkt2));
    memset(&pkt3, 0, sizeof(pkt3));

    if (!TEST_true( PACKET_buf_init( &pkt, data, len ) )
               /* Skip the record header */
            || !PACKET_forward(&pkt, SSL3_RT_HEADER_LENGTH)
               /* Skip the handshake message header */
            || !TEST_true(PACKET_forward(&pkt, SSL3_HM_HEADER_LENGTH))
               /* Skip client version and random */
            || !TEST_true(PACKET_forward(&pkt, CLIENT_VERSION_LEN
                                               + SSL3_RANDOM_SIZE))
               /* Skip session id */
            || !TEST_true(PACKET_get_length_prefixed_1(&pkt, &pkt2))
               /* Skip ciphers */
            || !TEST_true(PACKET_get_length_prefixed_2(&pkt, &pkt2))
               /* Skip compression */
            || !TEST_true(PACKET_get_length_prefixed_1(&pkt, &pkt2))
               /* Extensions len */
            || !TEST_true(PACKET_as_length_prefixed_2(&pkt, &pkt2)))
        goto end;

    /* Loop through all extensions */
    while (PACKET_remaining(&pkt2)) {
        if (!TEST_true(PACKET_get_net_2(&pkt2, &type))
                || !TEST_true(PACKET_get_length_prefixed_2(&pkt2, &pkt3)))
            goto end;

        if (type == TLSEXT_TYPE_max_fragment_length) {
            if (!TEST_uint_ne(PACKET_remaining(&pkt3), 0)
                    || !TEST_true(PACKET_get_1(&pkt3, &MFL_code)))
                goto end;

            *mfl_codemfl_code = MFL_code;
            return 1;
        }
    }

 end:
    return 0;
}