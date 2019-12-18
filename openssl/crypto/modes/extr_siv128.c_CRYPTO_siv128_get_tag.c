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
struct TYPE_4__ {int /*<<< orphan*/  byte; } ;
struct TYPE_5__ {TYPE_1__ tag; } ;
typedef  TYPE_2__ SIV128_CONTEXT ;

/* Variables and functions */
 size_t SIV_LEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

int CRYPTO_siv128_get_tag(SIV128_CONTEXT *ctx, unsigned char *tag, size_t len)
{
    if (len != SIV_LEN)
        return 0;

    /* Copy the tag into the supplied buffer */
    memcpy(tag, ctx->tag.byte, len);
    return 1;
}