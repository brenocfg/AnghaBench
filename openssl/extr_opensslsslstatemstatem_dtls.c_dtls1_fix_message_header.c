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
struct hm_header_st {size_t frag_off; size_t frag_len; } ;
struct TYPE_5__ {TYPE_1__* d1; } ;
struct TYPE_4__ {struct hm_header_st w_msg_hdr; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */

__attribute__((used)) static void
dtls1_fix_message_header(SSL *s, size_t frag_off, size_t frag_len)
{
    struct hm_header_st *msg_hdr = &s->d1->w_msg_hdr;

    msg_hdr->frag_off = frag_off;
    msg_hdr->frag_len = frag_len;
}