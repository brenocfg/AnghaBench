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

/* Variables and functions */
 int DTLS1_HM_HEADER_LENGTH ; 
 int DTLS1_RT_HEADER_LENGTH ; 
 size_t MSG_FRAG_LEN_HI ; 
 size_t MSG_FRAG_LEN_LO ; 
 size_t MSG_FRAG_LEN_MID ; 
 size_t MSG_FRAG_OFF_HI ; 
 size_t MSG_FRAG_OFF_LO ; 
 size_t MSG_FRAG_OFF_MID ; 
 size_t MSG_LEN_HI ; 
 size_t MSG_LEN_LO ; 
 size_t MSG_LEN_MID ; 
 size_t MSG_SEQ_HI ; 
 size_t MSG_SEQ_LO ; 
 size_t MSG_TYPE ; 
 size_t RECORD_CONTENT_TYPE ; 
 size_t RECORD_EPOCH_HI ; 
 size_t RECORD_EPOCH_LO ; 
 size_t RECORD_LEN_HI ; 
 size_t RECORD_LEN_LO ; 
 int RECORD_SEQUENCE_END ; 
 int RECORD_SEQUENCE_START ; 
 size_t RECORD_VERSION_HI ; 
 size_t RECORD_VERSION_LO ; 
 int SSL3_RT_HANDSHAKE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void dump_data(const char *data, int len)
{
    int rem, i, content, reclen, msglen, fragoff, fraglen, epoch;
    unsigned char *rec;

    printf("---- START OF PACKET ----\n");

    rem = len;
    rec = (unsigned char *)data;

    while (rem > 0) {
        if (rem != len)
            printf("*\n");
        printf("*---- START OF RECORD ----\n");
        if (rem < DTLS1_RT_HEADER_LENGTH) {
            printf("*---- RECORD TRUNCATED ----\n");
            break;
        }
        content = rec[RECORD_CONTENT_TYPE];
        printf("** Record Content-type: %d\n", content);
        printf("** Record Version: %02x%02x\n",
               rec[RECORD_VERSION_HI], rec[RECORD_VERSION_LO]);
        epoch = (rec[RECORD_EPOCH_HI] << 8) | rec[RECORD_EPOCH_LO];
        printf("** Record Epoch: %d\n", epoch);
        printf("** Record Sequence: ");
        for (i = RECORD_SEQUENCE_START; i <= RECORD_SEQUENCE_END; i++)
            printf("%02x", rec[i]);
        reclen = (rec[RECORD_LEN_HI] << 8) | rec[RECORD_LEN_LO];
        printf("\n** Record Length: %d\n", reclen);

        /* Now look at message */
        rec += DTLS1_RT_HEADER_LENGTH;
        rem -= DTLS1_RT_HEADER_LENGTH;
        if (content == SSL3_RT_HANDSHAKE) {
            printf("**---- START OF HANDSHAKE MESSAGE FRAGMENT ----\n");
            if (epoch > 0) {
                printf("**---- HANDSHAKE MESSAGE FRAGMENT ENCRYPTED ----\n");
            } else if (rem < DTLS1_HM_HEADER_LENGTH
                    || reclen < DTLS1_HM_HEADER_LENGTH) {
                printf("**---- HANDSHAKE MESSAGE FRAGMENT TRUNCATED ----\n");
            } else {
                printf("*** Message Type: %d\n", rec[MSG_TYPE]);
                msglen = (rec[MSG_LEN_HI] << 16) | (rec[MSG_LEN_MID] << 8)
                         | rec[MSG_LEN_LO];
                printf("*** Message Length: %d\n", msglen);
                printf("*** Message sequence: %d\n",
                       (rec[MSG_SEQ_HI] << 8) | rec[MSG_SEQ_LO]);
                fragoff = (rec[MSG_FRAG_OFF_HI] << 16)
                          | (rec[MSG_FRAG_OFF_MID] << 8)
                          | rec[MSG_FRAG_OFF_LO];
                printf("*** Message Fragment offset: %d\n", fragoff);
                fraglen = (rec[MSG_FRAG_LEN_HI] << 16)
                          | (rec[MSG_FRAG_LEN_MID] << 8)
                          | rec[MSG_FRAG_LEN_LO];
                printf("*** Message Fragment len: %d\n", fraglen);
                if (fragoff + fraglen > msglen)
                    printf("***---- HANDSHAKE MESSAGE FRAGMENT INVALID ----\n");
                else if (reclen < fraglen)
                    printf("**---- HANDSHAKE MESSAGE FRAGMENT TRUNCATED ----\n");
                else
                    printf("**---- END OF HANDSHAKE MESSAGE FRAGMENT ----\n");
            }
        }
        if (rem < reclen) {
            printf("*---- RECORD TRUNCATED ----\n");
            rem = 0;
        } else {
            rec += reclen;
            rem -= reclen;
            printf("*---- END OF RECORD ----\n");
        }
    }
    printf("---- END OF PACKET ----\n\n");
    fflush(stdout);
}