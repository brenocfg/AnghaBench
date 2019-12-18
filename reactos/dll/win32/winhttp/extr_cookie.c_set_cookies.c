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
struct attr {char* value; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  session_t ;
struct TYPE_5__ {int /*<<< orphan*/  path; TYPE_1__* connect; } ;
typedef  TYPE_2__ request_t ;
typedef  int /*<<< orphan*/  cookie_t ;
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  servername; int /*<<< orphan*/ * session; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_attr (struct attr*) ; 
 int /*<<< orphan*/  free_cookie (int /*<<< orphan*/ *) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 struct attr* parse_attr (char*,int*) ; 
 int /*<<< orphan*/ * parse_cookie (char*) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 char* strdupW (int /*<<< orphan*/ ) ; 
 int strlenW (char const*) ; 
 char* strrchrW (char*,char) ; 

BOOL set_cookies( request_t *request, const WCHAR *cookies )
{
    static const WCHAR pathW[] = {'p','a','t','h',0};
    static const WCHAR domainW[] = {'d','o','m','a','i','n',0};
    BOOL ret = FALSE;
    WCHAR *buffer, *p;
    WCHAR *cookie_domain = NULL, *cookie_path = NULL;
    struct attr *attr, *domain = NULL, *path = NULL;
    session_t *session = request->connect->session;
    cookie_t *cookie;
    int len, used;

    len = strlenW( cookies );
    if (!(buffer = heap_alloc( (len + 1) * sizeof(WCHAR) ))) return FALSE;
    strcpyW( buffer, cookies );

    p = buffer;
    while (*p && *p != ';') p++;
    if (*p == ';') *p++ = 0;
    if (!(cookie = parse_cookie( buffer )))
    {
        heap_free( buffer );
        return FALSE;
    }
    len = strlenW( p );
    while (len && (attr = parse_attr( p, &used )))
    {
        if (!strcmpiW( attr->name, domainW ))
        {
            domain = attr;
            cookie_domain = attr->value;
        }
        else if (!strcmpiW( attr->name, pathW ))
        {
            path = attr;
            cookie_path = attr->value;
        }
        else
        {
            FIXME( "unhandled attribute %s\n", debugstr_w(attr->name) );
            free_attr( attr );
        }
        len -= used;
        p += used;
    }
    if (!cookie_domain && !(cookie_domain = strdupW( request->connect->servername ))) goto end;
    if (!cookie_path && !(cookie_path = strdupW( request->path ))) goto end;

    if ((p = strrchrW( cookie_path, '/' )) && p != cookie_path) *p = 0;
    ret = add_cookie( session, cookie, cookie_domain, cookie_path );

end:
    if (!ret) free_cookie( cookie );
    if (domain) free_attr( domain );
    else heap_free( cookie_domain );
    if (path) free_attr( path );
    else heap_free( cookie_path );
    heap_free( buffer );
    return ret;
}