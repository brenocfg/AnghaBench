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
struct list {int dummy; } ;
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsACString ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ http_header_t ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  NS_ERROR_NOT_AVAILABLE ; 
 int /*<<< orphan*/  NS_ERROR_UNEXPECTED ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 TYPE_1__* find_http_header (struct list*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_strdupAtoW (char const*) ; 
 char* heap_strdupWtoA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsACString_GetData (int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  nsACString_SetData (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlenW (char*) ; 

__attribute__((used)) static nsresult get_channel_http_header(struct list *headers, const nsACString *header_name_str,
        nsACString *_retval)
{
    const char *header_namea;
    http_header_t *header;
    WCHAR *header_name;
    char *data;

    nsACString_GetData(header_name_str, &header_namea);
    header_name = heap_strdupAtoW(header_namea);
    if(!header_name)
        return NS_ERROR_UNEXPECTED;

    header = find_http_header(headers, header_name, strlenW(header_name));
    heap_free(header_name);
    if(!header)
        return NS_ERROR_NOT_AVAILABLE;

    data = heap_strdupWtoA(header->data);
    if(!data)
        return NS_ERROR_UNEXPECTED;

    TRACE("%s -> %s\n", debugstr_a(header_namea), debugstr_a(data));
    nsACString_SetData(_retval, data);
    heap_free(data);
    return NS_OK;
}