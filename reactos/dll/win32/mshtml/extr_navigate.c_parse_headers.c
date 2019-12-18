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
struct list {int dummy; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  set_http_header (struct list*,char const*,int,char const*,int) ; 

__attribute__((used)) static HRESULT parse_headers(const WCHAR *headers, struct list *headers_list)
{
    const WCHAR *header, *header_end, *colon, *value;
    HRESULT hres;

    header = headers;
    while(*header) {
        if(header[0] == '\r' && header[1] == '\n' && !header[2])
            break;
        for(colon = header; *colon && *colon != ':' && *colon != '\r'; colon++);
        if(*colon != ':')
            return E_FAIL;

        value = colon+1;
        while(*value == ' ')
            value++;
        if(!*value)
            return E_FAIL;

        for(header_end = value+1; *header_end && *header_end != '\r'; header_end++);

        hres = set_http_header(headers_list, header, colon-header, value, header_end-value);
        if(FAILED(hres))
            return hres;

        header = header_end;
        if(header[0] == '\r' && header[1] == '\n')
            header += 2;
    }

    return S_OK;
}