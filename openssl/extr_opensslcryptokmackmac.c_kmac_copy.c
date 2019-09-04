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
struct TYPE_4__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  custom_len; int /*<<< orphan*/  custom; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  xof_mode; int /*<<< orphan*/  out_len; int /*<<< orphan*/  md; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int EVP_MD_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmac_copy(EVP_MAC_IMPL *gdst, EVP_MAC_IMPL *gsrc)
{
    gdst->md = gsrc->md;
    gdst->out_len = gsrc->out_len;
    gdst->key_len = gsrc->key_len;
    gdst->custom_len = gsrc->custom_len;
    gdst->xof_mode = gsrc->xof_mode;
    memcpy(gdst->key, gsrc->key, gsrc->key_len);
    memcpy(gdst->custom, gsrc->custom, gdst->custom_len);

    return EVP_MD_CTX_copy(gdst->ctx, gsrc->ctx);
}