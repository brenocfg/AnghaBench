#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ ** CMS_get0_content (int /*<<< orphan*/ *) ; 

int CMS_is_detached(CMS_ContentInfo *cms)
{
    ASN1_OCTET_STRING **pos;

    pos = CMS_get0_content(cms);
    if (pos == NULL)
        return -1;
    if (*pos != NULL)
        return 0;
    return 1;
}