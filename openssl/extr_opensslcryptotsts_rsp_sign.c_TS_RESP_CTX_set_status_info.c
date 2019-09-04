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
struct TYPE_8__ {int /*<<< orphan*/  response; } ;
struct TYPE_7__ {int /*<<< orphan*/ * text; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ TS_STATUS_INFO ;
typedef  TYPE_2__ TS_RESP_CTX ;
typedef  int /*<<< orphan*/  ASN1_UTF8STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_UTF8STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_UTF8STRING_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_RESP_CTX_SET_STATUS_INFO ; 
 int /*<<< orphan*/  TS_RESP_set_status_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TS_STATUS_INFO_free (TYPE_1__*) ; 
 TYPE_1__* TS_STATUS_INFO_new () ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_ASN1_UTF8STRING_new_null () ; 
 int /*<<< orphan*/  sk_ASN1_UTF8STRING_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int TS_RESP_CTX_set_status_info(TS_RESP_CTX *ctx,
                                int status, const char *text)
{
    TS_STATUS_INFO *si = NULL;
    ASN1_UTF8STRING *utf8_text = NULL;
    int ret = 0;

    if ((si = TS_STATUS_INFO_new()) == NULL)
        goto err;
    if (!ASN1_INTEGER_set(si->status, status))
        goto err;
    if (text) {
        if ((utf8_text = ASN1_UTF8STRING_new()) == NULL
            || !ASN1_STRING_set(utf8_text, text, strlen(text)))
            goto err;
        if (si->text == NULL
            && (si->text = sk_ASN1_UTF8STRING_new_null()) == NULL)
            goto err;
        if (!sk_ASN1_UTF8STRING_push(si->text, utf8_text))
            goto err;
        utf8_text = NULL;       /* Ownership is lost. */
    }
    if (!TS_RESP_set_status_info(ctx->response, si))
        goto err;
    ret = 1;
 err:
    if (!ret)
        TSerr(TS_F_TS_RESP_CTX_SET_STATUS_INFO, ERR_R_MALLOC_FAILURE);
    TS_STATUS_INFO_free(si);
    ASN1_UTF8STRING_free(utf8_text);
    return ret;
}