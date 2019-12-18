#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* d1; } ;
struct TYPE_5__ {int /*<<< orphan*/  handshake_write_seq; int /*<<< orphan*/  next_handshake_write_seq; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  dtls1_set_message_header_int (TYPE_2__*,unsigned char,size_t,int /*<<< orphan*/ ,size_t,size_t) ; 

void dtls1_set_message_header(SSL *s,
                              unsigned char mt, size_t len,
                              size_t frag_off, size_t frag_len)
{
    if (frag_off == 0) {
        s->d1->handshake_write_seq = s->d1->next_handshake_write_seq;
        s->d1->next_handshake_write_seq++;
    }

    dtls1_set_message_header_int(s, mt, len, s->d1->handshake_write_seq,
                                 frag_off, frag_len);
}