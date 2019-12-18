#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {struct TYPE_13__* next; struct TYPE_13__* prev; scalar_t__ active; TYPE_3__ const* cipher; } ;
struct TYPE_12__ {int algorithm_mkey; int algorithm_auth; int algorithm_enc; int algorithm_mac; scalar_t__ min_tls; scalar_t__ min_dtls; int /*<<< orphan*/  valid; } ;
struct TYPE_11__ {TYPE_1__* ssl3_enc; TYPE_3__* (* get_cipher ) (int) ;} ;
struct TYPE_10__ {int enc_flags; } ;
typedef  TYPE_2__ SSL_METHOD ;
typedef  TYPE_3__ SSL_CIPHER ;
typedef  TYPE_4__ CIPHER_ORDER ;

/* Variables and functions */
 int SSL_ENC_FLAG_DTLS ; 
 TYPE_3__* stub1 (int) ; 

__attribute__((used)) static void ssl_cipher_collect_ciphers(const SSL_METHOD *ssl_method,
                                       int num_of_ciphers,
                                       uint32_t disabled_mkey,
                                       uint32_t disabled_auth,
                                       uint32_t disabled_enc,
                                       uint32_t disabled_mac,
                                       CIPHER_ORDER *co_list,
                                       CIPHER_ORDER **head_p,
                                       CIPHER_ORDER **tail_p)
{
    int i, co_list_num;
    const SSL_CIPHER *c;

    /*
     * We have num_of_ciphers descriptions compiled in, depending on the
     * method selected (SSLv3, TLSv1 etc).
     * These will later be sorted in a linked list with at most num
     * entries.
     */

    /* Get the initial list of ciphers */
    co_list_num = 0;            /* actual count of ciphers */
    for (i = 0; i < num_of_ciphers; i++) {
        c = ssl_method->get_cipher(i);
        /* drop those that use any of that is not available */
        if (c == NULL || !c->valid)
            continue;
        if ((c->algorithm_mkey & disabled_mkey) ||
            (c->algorithm_auth & disabled_auth) ||
            (c->algorithm_enc & disabled_enc) ||
            (c->algorithm_mac & disabled_mac))
            continue;
        if (((ssl_method->ssl3_enc->enc_flags & SSL_ENC_FLAG_DTLS) == 0) &&
            c->min_tls == 0)
            continue;
        if (((ssl_method->ssl3_enc->enc_flags & SSL_ENC_FLAG_DTLS) != 0) &&
            c->min_dtls == 0)
            continue;

        co_list[co_list_num].cipher = c;
        co_list[co_list_num].next = NULL;
        co_list[co_list_num].prev = NULL;
        co_list[co_list_num].active = 0;
        co_list_num++;
    }

    /*
     * Prepare linked list from list entries
     */
    if (co_list_num > 0) {
        co_list[0].prev = NULL;

        if (co_list_num > 1) {
            co_list[0].next = &co_list[1];

            for (i = 1; i < co_list_num - 1; i++) {
                co_list[i].prev = &co_list[i - 1];
                co_list[i].next = &co_list[i + 1];
            }

            co_list[co_list_num - 1].prev = &co_list[co_list_num - 2];
        }

        co_list[co_list_num - 1].next = NULL;

        *head_p = &co_list[0];
        *tail_p = &co_list[co_list_num - 1];
    }
}