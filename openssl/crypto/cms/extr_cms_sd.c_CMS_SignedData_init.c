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

/* Variables and functions */
 scalar_t__ cms_signed_data_init (int /*<<< orphan*/ *) ; 

int CMS_SignedData_init(CMS_ContentInfo *cms)
{
    if (cms_signed_data_init(cms))
        return 1;
    else
        return 0;
}