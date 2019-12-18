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
struct TYPE_4__ {int /*<<< orphan*/  responseExtensions; } ;
struct TYPE_5__ {TYPE_1__ tbsResponseData; } ;
typedef  TYPE_2__ OCSP_BASICRESP ;

/* Variables and functions */
 int ocsp_add1_nonce (int /*<<< orphan*/ *,unsigned char*,int) ; 

int OCSP_basic_add1_nonce(OCSP_BASICRESP *resp, unsigned char *val, int len)
{
    return ocsp_add1_nonce(&resp->tbsResponseData.responseExtensions, val,
                           len);
}