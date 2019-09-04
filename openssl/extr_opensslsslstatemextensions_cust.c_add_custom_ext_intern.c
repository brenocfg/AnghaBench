#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int meths_count; TYPE_3__* meths; } ;
typedef  TYPE_2__ custom_ext_methods ;
struct TYPE_13__ {unsigned int context; unsigned int ext_type; void* parse_arg; void* add_arg; int /*<<< orphan*/ * free_cb; int /*<<< orphan*/ * add_cb; int /*<<< orphan*/  parse_cb; int /*<<< orphan*/  role; } ;
typedef  TYPE_3__ custom_ext_method ;
struct TYPE_14__ {TYPE_1__* cert; } ;
struct TYPE_11__ {TYPE_2__ custext; } ;
typedef  int /*<<< orphan*/  SSL_custom_ext_parse_cb_ex ;
typedef  int /*<<< orphan*/ * SSL_custom_ext_free_cb_ex ;
typedef  int /*<<< orphan*/ * SSL_custom_ext_add_cb_ex ;
typedef  TYPE_4__ SSL_CTX ;
typedef  int /*<<< orphan*/  ENDPOINT ;

/* Variables and functions */
 TYPE_3__* OPENSSL_realloc (TYPE_3__*,int) ; 
 scalar_t__ SSL_CTX_ct_is_enabled (TYPE_4__*) ; 
 unsigned int SSL_EXT_CLIENT_HELLO ; 
 scalar_t__ SSL_extension_supported (unsigned int) ; 
 unsigned int TLSEXT_TYPE_signed_certificate_timestamp ; 
 scalar_t__ custom_ext_find (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int add_custom_ext_intern(SSL_CTX *ctx, ENDPOINT role,
                                 unsigned int ext_type,
                                 unsigned int context,
                                 SSL_custom_ext_add_cb_ex add_cb,
                                 SSL_custom_ext_free_cb_ex free_cb,
                                 void *add_arg,
                                 SSL_custom_ext_parse_cb_ex parse_cb,
                                 void *parse_arg)
{
    custom_ext_methods *exts = &ctx->cert->custext;
    custom_ext_method *meth, *tmp;

    /*
     * Check application error: if add_cb is not set free_cb will never be
     * called.
     */
    if (add_cb == NULL && free_cb != NULL)
        return 0;

#ifndef OPENSSL_NO_CT
    /*
     * We don't want applications registering callbacks for SCT extensions
     * whilst simultaneously using the built-in SCT validation features, as
     * these two things may not play well together.
     */
    if (ext_type == TLSEXT_TYPE_signed_certificate_timestamp
            && (context & SSL_EXT_CLIENT_HELLO) != 0
            && SSL_CTX_ct_is_enabled(ctx))
        return 0;
#endif

    /*
     * Don't add if extension supported internally, but make exception
     * for extension types that previously were not supported, but now are.
     */
    if (SSL_extension_supported(ext_type)
            && ext_type != TLSEXT_TYPE_signed_certificate_timestamp)
        return 0;

    /* Extension type must fit in 16 bits */
    if (ext_type > 0xffff)
        return 0;
    /* Search for duplicate */
    if (custom_ext_find(exts, role, ext_type, NULL))
        return 0;
    tmp = OPENSSL_realloc(exts->meths,
                          (exts->meths_count + 1) * sizeof(custom_ext_method));
    if (tmp == NULL)
        return 0;

    exts->meths = tmp;
    meth = exts->meths + exts->meths_count;
    memset(meth, 0, sizeof(*meth));
    meth->role = role;
    meth->context = context;
    meth->parse_cb = parse_cb;
    meth->add_cb = add_cb;
    meth->free_cb = free_cb;
    meth->ext_type = ext_type;
    meth->add_arg = add_arg;
    meth->parse_arg = parse_arg;
    exts->meths_count++;
    return 1;
}