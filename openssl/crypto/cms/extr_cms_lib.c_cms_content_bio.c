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
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_FLAG_CONT ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_s_null () ; 
 TYPE_1__** CMS_get0_content (int /*<<< orphan*/ *) ; 

BIO *cms_content_bio(CMS_ContentInfo *cms)
{
    ASN1_OCTET_STRING **pos = CMS_get0_content(cms);

    if (pos == NULL)
        return NULL;
    /* If content detached data goes nowhere: create NULL BIO */
    if (*pos == NULL)
        return BIO_new(BIO_s_null());
    /*
     * If content not detached and created return memory BIO
     */
    if (*pos == NULL || ((*pos)->flags == ASN1_STRING_FLAG_CONT))
        return BIO_new(BIO_s_mem());
    /* Else content was read in: return read only BIO for it */
    return BIO_new_mem_buf((*pos)->data, (*pos)->length);
}