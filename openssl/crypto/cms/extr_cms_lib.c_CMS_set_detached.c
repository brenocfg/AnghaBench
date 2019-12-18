#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_FLAG_CONT ; 
 int /*<<< orphan*/  CMS_F_CMS_SET_DETACHED ; 
 TYPE_1__** CMS_get0_content (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 

int CMS_set_detached(CMS_ContentInfo *cms, int detached)
{
    ASN1_OCTET_STRING **pos;

    pos = CMS_get0_content(cms);
    if (pos == NULL)
        return 0;
    if (detached) {
        ASN1_OCTET_STRING_free(*pos);
        *pos = NULL;
        return 1;
    }
    if (*pos == NULL)
        *pos = ASN1_OCTET_STRING_new();
    if (*pos != NULL) {
        /*
         * NB: special flag to show content is created and not read in.
         */
        (*pos)->flags |= ASN1_STRING_FLAG_CONT;
        return 1;
    }
    CMSerr(CMS_F_CMS_SET_DETACHED, ERR_R_MALLOC_FAILURE);
    return 0;
}