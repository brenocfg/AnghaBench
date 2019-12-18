#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* sig; size_t sig_len; int /*<<< orphan*/  validation_status; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  SCT_VALIDATION_STATUS_NOT_SET ; 

void SCT_set0_signature(SCT *sct, unsigned char *sig, size_t sig_len)
{
    OPENSSL_free(sct->sig);
    sct->sig = sig;
    sct->sig_len = sig_len;
    sct->validation_status = SCT_VALIDATION_STATUS_NOT_SET;
}