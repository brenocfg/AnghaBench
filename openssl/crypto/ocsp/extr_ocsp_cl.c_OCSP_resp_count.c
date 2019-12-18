#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  responses; } ;
struct TYPE_5__ {TYPE_1__ tbsResponseData; } ;
typedef  TYPE_2__ OCSP_BASICRESP ;

/* Variables and functions */
 int sk_OCSP_SINGLERESP_num (int /*<<< orphan*/ ) ; 

int OCSP_resp_count(OCSP_BASICRESP *bs)
{
    if (!bs)
        return -1;
    return sk_OCSP_SINGLERESP_num(bs->tbsResponseData.responses);
}