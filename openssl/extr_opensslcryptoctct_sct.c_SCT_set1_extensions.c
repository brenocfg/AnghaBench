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
struct TYPE_3__ {size_t ext_len; int /*<<< orphan*/ * ext; int /*<<< orphan*/  validation_status; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_SET1_EXTENSIONS ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_memdup (unsigned char const*,size_t) ; 
 int /*<<< orphan*/  SCT_VALIDATION_STATUS_NOT_SET ; 

int SCT_set1_extensions(SCT *sct, const unsigned char *ext, size_t ext_len)
{
    OPENSSL_free(sct->ext);
    sct->ext = NULL;
    sct->ext_len = 0;
    sct->validation_status = SCT_VALIDATION_STATUS_NOT_SET;

    if (ext != NULL && ext_len > 0) {
        sct->ext = OPENSSL_memdup(ext, ext_len);
        if (sct->ext == NULL) {
            CTerr(CT_F_SCT_SET1_EXTENSIONS, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        sct->ext_len = ext_len;
    }
    return 1;
}