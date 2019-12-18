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
struct TYPE_3__ {int /*<<< orphan*/  const tbsResponseData; } ;
typedef  int /*<<< orphan*/  OCSP_RESPDATA ;
typedef  TYPE_1__ OCSP_BASICRESP ;

/* Variables and functions */

const OCSP_RESPDATA *OCSP_resp_get0_respdata(const OCSP_BASICRESP *bs)
{
    return &bs->tbsResponseData;
}