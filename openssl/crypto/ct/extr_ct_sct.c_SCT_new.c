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
struct TYPE_4__ {int /*<<< orphan*/  version; int /*<<< orphan*/  entry_type; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_NEW ; 
 int /*<<< orphan*/  CT_LOG_ENTRY_TYPE_NOT_SET ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SCT_VERSION_NOT_SET ; 

SCT *SCT_new(void)
{
    SCT *sct = OPENSSL_zalloc(sizeof(*sct));

    if (sct == NULL) {
        CTerr(CT_F_SCT_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    sct->entry_type = CT_LOG_ENTRY_TYPE_NOT_SET;
    sct->version = SCT_VERSION_NOT_SET;
    return sct;
}