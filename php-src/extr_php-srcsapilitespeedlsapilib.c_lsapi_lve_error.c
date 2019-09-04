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
typedef  int /*<<< orphan*/  achBody ;
typedef  int /*<<< orphan*/  LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_ErrResponse_r (int /*<<< orphan*/ *,int,char const**,char const*,int) ; 

__attribute__((used)) static int lsapi_lve_error( LSAPI_Request * pReq )
{
    static const char * headers[] =
    {
        "Cache-Control: private, no-cache, no-store, must-revalidate, max-age=0",
        "Pragma: no-cache",
        "Retry-After: 60",
        "Content-Type: text/html",
        NULL
    };
    static const char achBody[] =
        "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n"
        "<HTML><HEAD>\n<TITLE>508 Resource Limit Is Reached</TITLE>\n"
        "</HEAD><BODY>\n" "<H1>Resource Limit Is Reached</H1>\n"
        "The website is temporarily unable to service your request as it exceeded resource limit.\n"
        "Please try again later.\n"
        "<HR>\n"
        "</BODY></HTML>\n";

    LSAPI_ErrResponse_r( pReq, 508, headers, achBody, sizeof( achBody ) - 1 );
    return 0;
}