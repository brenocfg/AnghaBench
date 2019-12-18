#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {int /*<<< orphan*/  s; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ DSA_SIG ;
typedef  TYPE_2__ BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (TYPE_2__*) ; 
 TYPE_2__* BUF_MEM_new () ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  WPACKET_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_init_len (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_init_null (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_init_static_len (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_der_dsa_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i2d_DSA_SIG(const DSA_SIG *sig, unsigned char **ppout)
{
    BUF_MEM *buf = NULL;
    size_t encoded_len;
    WPACKET pkt;

    if (ppout == NULL) {
        if (!WPACKET_init_null(&pkt, 0))
            return -1;
    } else if (*ppout == NULL) {
        if ((buf = BUF_MEM_new()) == NULL
                || !WPACKET_init_len(&pkt, buf, 0)) {
            BUF_MEM_free(buf);
            return -1;
        }
    } else {
        if (!WPACKET_init_static_len(&pkt, *ppout, SIZE_MAX, 0))
            return -1;
    }

    if (!encode_der_dsa_sig(&pkt, sig->r, sig->s)
            || !WPACKET_get_total_written(&pkt, &encoded_len)
            || !WPACKET_finish(&pkt)) {
        BUF_MEM_free(buf);
        WPACKET_cleanup(&pkt);
        return -1;
    }

    if (ppout != NULL) {
        if (*ppout == NULL) {
            *ppout = (unsigned char *)buf->data;
            buf->data = NULL;
            BUF_MEM_free(buf);
        } else {
            *ppout += encoded_len;
        }
    }

    return (int)encoded_len;
}