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
struct TYPE_6__ {int /*<<< orphan*/ * pctx; int /*<<< orphan*/  input; scalar_t__ is_oneshot; int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; int /*<<< orphan*/  osin_len; int /*<<< orphan*/  osin; int /*<<< orphan*/  md; int /*<<< orphan*/  ctx; scalar_t__ is_verify; } ;
struct TYPE_5__ {int skip; char* err; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_2__ DIGESTSIGN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestSignInit (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestVerifyInit (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int evp_test_buffer_append (char const*,int /*<<< orphan*/ *) ; 
 int evp_test_buffer_ncopy (char const*,int /*<<< orphan*/ ) ; 
 int evp_test_buffer_set_count (char const*,int /*<<< orphan*/ ) ; 
 int find_key (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int parse_bin (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pkey_test_ctrl (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  private_keys ; 
 int /*<<< orphan*/  public_keys ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int digestsigver_test_parse(EVP_TEST *t,
                                   const char *keyword, const char *value)
{
    DIGESTSIGN_DATA *mdata = t->data;

    if (strcmp(keyword, "Key") == 0) {
        EVP_PKEY *pkey = NULL;
        int rv = 0;

        if (mdata->is_verify)
            rv = find_key(&pkey, value, public_keys);
        if (rv == 0)
            rv = find_key(&pkey, value, private_keys);
        if (rv == 0 || pkey == NULL) {
            t->skip = 1;
            return 1;
        }
        if (mdata->is_verify) {
            if (!EVP_DigestVerifyInit(mdata->ctx, &mdata->pctx, mdata->md,
                                      NULL, pkey))
                t->err = "DIGESTVERIFYINIT_ERROR";
            return 1;
        }
        if (!EVP_DigestSignInit(mdata->ctx, &mdata->pctx, mdata->md, NULL,
                                pkey))
            t->err = "DIGESTSIGNINIT_ERROR";
        return 1;
    }

    if (strcmp(keyword, "Input") == 0) {
        if (mdata->is_oneshot)
            return parse_bin(value, &mdata->osin, &mdata->osin_len);
        return evp_test_buffer_append(value, &mdata->input);
    }
    if (strcmp(keyword, "Output") == 0)
        return parse_bin(value, &mdata->output, &mdata->output_len);

    if (!mdata->is_oneshot) {
        if (strcmp(keyword, "Count") == 0)
            return evp_test_buffer_set_count(value, mdata->input);
        if (strcmp(keyword, "Ncopy") == 0)
            return evp_test_buffer_ncopy(value, mdata->input);
    }
    if (strcmp(keyword, "Ctrl") == 0) {
        if (mdata->pctx == NULL)
            return -1;
        return pkey_test_ctrl(t, mdata->pctx, value);
    }
    return 0;
}