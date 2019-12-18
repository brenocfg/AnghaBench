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
struct TYPE_5__ {char* path; TYPE_1__* server; } ;
typedef  TYPE_2__ http_request_t ;
typedef  char WCHAR ;
struct TYPE_4__ {char* canon_host_port; scalar_t__ is_https; } ;

/* Variables and functions */
 char* heap_alloc (size_t) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static WCHAR *compose_request_url(http_request_t *req)
{
    static const WCHAR http[] = { 'h','t','t','p',':','/','/',0 };
    static const WCHAR https[] = { 'h','t','t','p','s',':','/','/',0 };
    const WCHAR *host, *scheme;
    WCHAR *buf, *ptr;
    size_t len;

    host = req->server->canon_host_port;

    if (req->server->is_https)
        scheme = https;
    else
        scheme = http;

    len = strlenW(scheme) + strlenW(host) + (req->path[0] != '/' ? 1 : 0) + strlenW(req->path);
    ptr = buf = heap_alloc((len+1) * sizeof(WCHAR));
    if(buf) {
        strcpyW(ptr, scheme);
        ptr += strlenW(ptr);

        strcpyW(ptr, host);
        ptr += strlenW(ptr);

        if(req->path[0] != '/')
            *ptr++ = '/';

        strcpyW(ptr, req->path);
        ptr += strlenW(ptr);
        *ptr = 0;
    }

    return buf;
}