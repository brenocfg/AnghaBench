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
typedef  int /*<<< orphan*/  OCSP_RESPONSE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2d_OCSP_RESPONSE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_OCSP_RESPONSE_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_ocsp_response(BIO *cbio, OCSP_RESPONSE *resp)
{
    char http_resp[] =
        "HTTP/1.0 200 OK\r\nContent-type: application/ocsp-response\r\n"
        "Content-Length: %d\r\n\r\n";
    if (cbio == NULL)
        return 0;
    BIO_printf(cbio, http_resp, i2d_OCSP_RESPONSE(resp, NULL));
    i2d_OCSP_RESPONSE_bio(cbio, resp);
    (void)BIO_flush(cbio);
    return 1;
}