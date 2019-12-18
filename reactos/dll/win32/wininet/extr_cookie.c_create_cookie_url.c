#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
struct TYPE_5__ {int len; char* str; } ;
typedef  TYPE_1__ substr_t ;
typedef  int /*<<< orphan*/  cookie_prefix ;
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 char* FALSE ; 
 int /*<<< orphan*/  GetUserNameW (char*,int*) ; 
 int UNLEN ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char tolowerW (char) ; 

__attribute__((used)) static WCHAR *create_cookie_url(substr_t domain, substr_t path, substr_t *ret_path)
{
    WCHAR user[UNLEN], *p, *url;
    DWORD len, user_len, i;

    static const WCHAR cookie_prefix[] = {'C','o','o','k','i','e',':'};

    user_len = sizeof(user)/sizeof(WCHAR);
    if(!GetUserNameW(user, &user_len))
        return FALSE;
    user_len--;

    len = sizeof(cookie_prefix)/sizeof(WCHAR) + user_len + 1 /* @ */ + domain.len + path.len;
    url = heap_alloc((len+1) * sizeof(WCHAR));
    if(!url)
        return NULL;

    memcpy(url, cookie_prefix, sizeof(cookie_prefix));
    p = url + sizeof(cookie_prefix)/sizeof(WCHAR);

    memcpy(p, user, user_len*sizeof(WCHAR));
    p += user_len;

    *p++ = '@';

    memcpy(p, domain.str, domain.len*sizeof(WCHAR));
    p += domain.len;

    for(i=0; i < path.len; i++)
        p[i] = tolowerW(path.str[i]);
    p[path.len] = 0;

    ret_path->str = p;
    ret_path->len = path.len;
    return url;
}