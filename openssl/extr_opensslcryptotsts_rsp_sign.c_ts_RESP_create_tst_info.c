#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dirn; } ;
struct TYPE_15__ {TYPE_2__ d; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int flags; int /*<<< orphan*/  signer_cert; TYPE_1__* request; int /*<<< orphan*/  micros; int /*<<< orphan*/  millis; int /*<<< orphan*/  seconds; int /*<<< orphan*/  clock_precision_digits; int /*<<< orphan*/  time_cb_data; int /*<<< orphan*/  (* time_cb ) (TYPE_3__*,int /*<<< orphan*/ ,long*,long*) ;int /*<<< orphan*/  serial_cb_data; int /*<<< orphan*/ * (* serial_cb ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/ * nonce; int /*<<< orphan*/  msg_imprint; } ;
typedef  int /*<<< orphan*/  TS_TST_INFO ;
typedef  TYPE_3__ TS_RESP_CTX ;
typedef  int /*<<< orphan*/  TS_ACCURACY ;
typedef  TYPE_4__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERAL_NAME_free (TYPE_4__*) ; 
 TYPE_4__* GENERAL_NAME_new () ; 
 int /*<<< orphan*/  GEN_DIRNAME ; 
 int /*<<< orphan*/  TS_ACCURACY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_ACCURACY_new () ; 
 int /*<<< orphan*/  TS_ACCURACY_set_micros (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_ACCURACY_set_millis (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_ACCURACY_set_seconds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_F_TS_RESP_CREATE_TST_INFO ; 
 int TS_ORDERING ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_status_info_cond (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * TS_RESP_set_genTime_with_precision (int /*<<< orphan*/ *,long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_R_TST_INFO_SETUP_ERROR ; 
 int /*<<< orphan*/  TS_STATUS_REJECTION ; 
 int TS_TSA_NAME ; 
 int /*<<< orphan*/  TS_TST_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_TST_INFO_new () ; 
 int /*<<< orphan*/  TS_TST_INFO_set_accuracy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_msg_imprint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_nonce (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_ordering (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_policy_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_serial (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_tsa (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  TS_TST_INFO_set_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,long*,long*) ; 

__attribute__((used)) static TS_TST_INFO *ts_RESP_create_tst_info(TS_RESP_CTX *ctx,
                                            ASN1_OBJECT *policy)
{
    int result = 0;
    TS_TST_INFO *tst_info = NULL;
    ASN1_INTEGER *serial = NULL;
    ASN1_GENERALIZEDTIME *asn1_time = NULL;
    long sec, usec;
    TS_ACCURACY *accuracy = NULL;
    const ASN1_INTEGER *nonce;
    GENERAL_NAME *tsa_name = NULL;

    if ((tst_info = TS_TST_INFO_new()) == NULL)
        goto end;
    if (!TS_TST_INFO_set_version(tst_info, 1))
        goto end;
    if (!TS_TST_INFO_set_policy_id(tst_info, policy))
        goto end;
    if (!TS_TST_INFO_set_msg_imprint(tst_info, ctx->request->msg_imprint))
        goto end;
    if ((serial = ctx->serial_cb(ctx, ctx->serial_cb_data)) == NULL
        || !TS_TST_INFO_set_serial(tst_info, serial))
        goto end;
    if (!ctx->time_cb(ctx, ctx->time_cb_data, &sec, &usec)
        || (asn1_time =
            TS_RESP_set_genTime_with_precision(NULL, sec, usec,
                                        ctx->clock_precision_digits)) == NULL
        || !TS_TST_INFO_set_time(tst_info, asn1_time))
        goto end;

    if ((ctx->seconds || ctx->millis || ctx->micros)
        && (accuracy = TS_ACCURACY_new()) == NULL)
        goto end;
    if (ctx->seconds && !TS_ACCURACY_set_seconds(accuracy, ctx->seconds))
        goto end;
    if (ctx->millis && !TS_ACCURACY_set_millis(accuracy, ctx->millis))
        goto end;
    if (ctx->micros && !TS_ACCURACY_set_micros(accuracy, ctx->micros))
        goto end;
    if (accuracy && !TS_TST_INFO_set_accuracy(tst_info, accuracy))
        goto end;

    if ((ctx->flags & TS_ORDERING)
        && !TS_TST_INFO_set_ordering(tst_info, 1))
        goto end;

    if ((nonce = ctx->request->nonce) != NULL
        && !TS_TST_INFO_set_nonce(tst_info, nonce))
        goto end;

    if (ctx->flags & TS_TSA_NAME) {
        if ((tsa_name = GENERAL_NAME_new()) == NULL)
            goto end;
        tsa_name->type = GEN_DIRNAME;
        tsa_name->d.dirn =
            X509_NAME_dup(X509_get_subject_name(ctx->signer_cert));
        if (!tsa_name->d.dirn)
            goto end;
        if (!TS_TST_INFO_set_tsa(tst_info, tsa_name))
            goto end;
    }

    result = 1;
 end:
    if (!result) {
        TS_TST_INFO_free(tst_info);
        tst_info = NULL;
        TSerr(TS_F_TS_RESP_CREATE_TST_INFO, TS_R_TST_INFO_SETUP_ERROR);
        TS_RESP_CTX_set_status_info_cond(ctx, TS_STATUS_REJECTION,
                                         "Error during TSTInfo "
                                         "generation.");
    }
    GENERAL_NAME_free(tsa_name);
    TS_ACCURACY_free(accuracy);
    ASN1_GENERALIZEDTIME_free(asn1_time);
    ASN1_INTEGER_free(serial);

    return tst_info;
}