#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; scalar_t__ data; } ;
typedef  TYPE_1__ BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_COLLECT_DATA ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUF_MEM_grow_clean (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,long) ; 

__attribute__((used)) static int collect_data(BUF_MEM *buf, const unsigned char **p, long plen)
{
    int len;
    if (buf) {
        len = buf->length;
        if (!BUF_MEM_grow_clean(buf, len + plen)) {
            ASN1err(ASN1_F_COLLECT_DATA, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        memcpy(buf->data + len, *p, plen);
    }
    *p += plen;
    return 1;
}