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
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_write (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_should_write (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 unsigned int SSL3_MT_CLIENT_HELLO ; 
 unsigned int SSL3_MT_SERVER_HELLO ; 
 unsigned int SSL3_RT_APPLICATION_DATA ; 
 unsigned int SSL3_RT_CHANGE_CIPHER_SPEC ; 
 unsigned int SSL3_RT_HANDSHAKE ; 
 unsigned int TLS1_2_VERSION ; 
 unsigned int TLS1_VERSION ; 
 int badccs ; 
 int badsessid ; 
 int badvers ; 
 int cappdataseen ; 
 int ccsaftersh ; 
 int ccsbeforesh ; 
 int chseen ; 
 int /*<<< orphan*/  chsessid ; 
 scalar_t__ chsessidlen ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * s_to_c_fbio ; 
 int sappdataseen ; 
 int sccsseen ; 
 int shseen ; 

__attribute__((used)) static int watchccs_write(BIO *bio, const char *in, int inl)
{
    int ret = 0;
    BIO *next = BIO_next(bio);
    PACKET pkt, msg, msgbody, sessionid;
    unsigned int rectype, recvers, msgtype, expectedrecvers;

    if (inl <= 0)
        return 0;
    if (next == NULL)
        return 0;

    BIO_clear_retry_flags(bio);

    if (!PACKET_buf_init(&pkt, (const unsigned char *)in, inl))
        return 0;

    /* We assume that we always write complete records each time */
    while (PACKET_remaining(&pkt)) {
        if (!PACKET_get_1(&pkt, &rectype)
                || !PACKET_get_net_2(&pkt, &recvers)
                || !PACKET_get_length_prefixed_2(&pkt, &msg))
            return 0;

        expectedrecvers = TLS1_2_VERSION;

        if (rectype == SSL3_RT_HANDSHAKE) {
            if (!PACKET_get_1(&msg, &msgtype)
                    || !PACKET_get_length_prefixed_3(&msg, &msgbody))
                return 0;
            if (msgtype == SSL3_MT_CLIENT_HELLO) {
                chseen++;

                /*
                 * Skip legacy_version (2 bytes) and Random (32 bytes) to read
                 * session_id.
                 */
                if (!PACKET_forward(&msgbody, 34)
                        || !PACKET_get_length_prefixed_1(&msgbody, &sessionid))
                    return 0;

                if (chseen == 1) {
                    expectedrecvers = TLS1_VERSION;

                    /* Save the session id for later */
                    chsessidlen = PACKET_remaining(&sessionid);
                    if (!PACKET_copy_bytes(&sessionid, chsessid, chsessidlen))
                        return 0;
                } else {
                    /*
                     * Check the session id for the second ClientHello is the
                     * same as the first one.
                     */
                    if (PACKET_remaining(&sessionid) != chsessidlen
                            || (chsessidlen > 0
                                && memcmp(chsessid, PACKET_data(&sessionid),
                                          chsessidlen) != 0))
                        badsessid = 1;
                }
            } else if (msgtype == SSL3_MT_SERVER_HELLO) {
                shseen++;
                /*
                 * Skip legacy_version (2 bytes) and Random (32 bytes) to read
                 * session_id.
                 */
                if (!PACKET_forward(&msgbody, 34)
                        || !PACKET_get_length_prefixed_1(&msgbody, &sessionid))
                    return 0;

                /*
                 * Check the session id is the same as the one in the
                 * ClientHello
                 */
                if (PACKET_remaining(&sessionid) != chsessidlen
                        || (chsessidlen > 0
                            && memcmp(chsessid, PACKET_data(&sessionid),
                                      chsessidlen) != 0))
                    badsessid = 1;
            }
        } else if (rectype == SSL3_RT_CHANGE_CIPHER_SPEC) {
            if (bio == s_to_c_fbio) {
                /*
                 * Server writing. We shouldn't have written any app data
                 * yet, and we should have seen both the ClientHello and the
                 * ServerHello
                 */
                if (!sappdataseen
                        && chseen == 1
                        && shseen == 1
                        && !sccsseen)
                    sccsseen = 1;
                else
                    badccs = 1;
            } else if (!cappdataseen) {
                /*
                 * Client writing. We shouldn't have written any app data
                 * yet, and we should have seen the ClientHello
                 */
                if (shseen == 1 && !ccsaftersh)
                    ccsaftersh = 1;
                else if (shseen == 0 && !ccsbeforesh)
                    ccsbeforesh = 1;
                else
                    badccs = 1;
            } else {
                badccs = 1;
            }
        } else if(rectype == SSL3_RT_APPLICATION_DATA) {
            if (bio == s_to_c_fbio)
                sappdataseen = 1;
            else
                cappdataseen = 1;
        }
        if (recvers != expectedrecvers)
            badvers = 1;
    }

    ret = BIO_write(next, in, inl);
    if (ret <= 0 && BIO_should_write(next))
        BIO_set_retry_write(bio);

    return ret;
}