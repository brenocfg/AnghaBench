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
struct TYPE_4__ {scalar_t__ log_id_len; scalar_t__ version; scalar_t__ sct_len; scalar_t__ ext_len; scalar_t__ sig_len; int /*<<< orphan*/  sig; int /*<<< orphan*/  ext; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  log_id; int /*<<< orphan*/  sct; } ;
typedef  TYPE_1__ SCT ;
typedef  int /*<<< orphan*/  CTLOG_STORE ;
typedef  int /*<<< orphan*/  CTLOG ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_hex_string (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * CTLOG_STORE_get0_log_by_id (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CTLOG_get0_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ SCT_VERSION_V1 ; 
 int /*<<< orphan*/  SCT_signature_algorithms_print (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timestamp_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void SCT_print(const SCT *sct, BIO *out, int indent,
               const CTLOG_STORE *log_store)
{
    const CTLOG *log = NULL;

    if (log_store != NULL) {
        log = CTLOG_STORE_get0_log_by_id(log_store, sct->log_id,
                                         sct->log_id_len);
    }

    BIO_printf(out, "%*sSigned Certificate Timestamp:", indent, "");
    BIO_printf(out, "\n%*sVersion   : ", indent + 4, "");

    if (sct->version != SCT_VERSION_V1) {
        BIO_printf(out, "unknown\n%*s", indent + 16, "");
        BIO_hex_string(out, indent + 16, 16, sct->sct, sct->sct_len);
        return;
    }

    BIO_printf(out, "v1 (0x0)");

    if (log != NULL) {
        BIO_printf(out, "\n%*sLog       : %s", indent + 4, "",
                   CTLOG_get0_name(log));
    }

    BIO_printf(out, "\n%*sLog ID    : ", indent + 4, "");
    BIO_hex_string(out, indent + 16, 16, sct->log_id, sct->log_id_len);

    BIO_printf(out, "\n%*sTimestamp : ", indent + 4, "");
    timestamp_print(sct->timestamp, out);

    BIO_printf(out, "\n%*sExtensions: ", indent + 4, "");
    if (sct->ext_len == 0)
        BIO_printf(out, "none");
    else
        BIO_hex_string(out, indent + 16, 16, sct->ext, sct->ext_len);

    BIO_printf(out, "\n%*sSignature : ", indent + 4, "");
    SCT_signature_algorithms_print(sct, out);
    BIO_printf(out, "\n%*s            ", indent + 4, "");
    BIO_hex_string(out, indent + 16, 16, sct->sig, sct->sig_len);
}