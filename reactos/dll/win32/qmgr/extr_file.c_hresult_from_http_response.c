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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BG_E_HTTP_ERROR_400 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_401 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_404 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_407 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_414 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_501 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_503 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_504 ; 
 int /*<<< orphan*/  BG_E_HTTP_ERROR_505 ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT hresult_from_http_response(DWORD code)
{
    switch (code)
    {
    case 200: return S_OK;
    case 400: return BG_E_HTTP_ERROR_400;
    case 401: return BG_E_HTTP_ERROR_401;
    case 404: return BG_E_HTTP_ERROR_404;
    case 407: return BG_E_HTTP_ERROR_407;
    case 414: return BG_E_HTTP_ERROR_414;
    case 501: return BG_E_HTTP_ERROR_501;
    case 503: return BG_E_HTTP_ERROR_503;
    case 504: return BG_E_HTTP_ERROR_504;
    case 505: return BG_E_HTTP_ERROR_505;
    default:
        FIXME("unhandled response code %u\n", code);
        return S_OK;
    }
}