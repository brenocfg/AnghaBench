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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsACString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  NS_ERROR_UNEXPECTED ; 
 int /*<<< orphan*/  NS_OK ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_strdupAtoW (char const*) ; 
 int /*<<< orphan*/  nsACString_GetData (int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  set_http_header (struct list*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static nsresult set_channel_http_header(struct list *headers, const nsACString *name_str,
        const nsACString *value_str)
{
    const char *namea, *valuea;
    WCHAR *name, *value;
    HRESULT hres;

    nsACString_GetData(name_str, &namea);
    name = heap_strdupAtoW(namea);
    if(!name)
        return NS_ERROR_UNEXPECTED;

    nsACString_GetData(value_str, &valuea);
    value = heap_strdupAtoW(valuea);
    if(!value) {
        heap_free(name);
        return NS_ERROR_UNEXPECTED;
    }

    hres = set_http_header(headers, name, strlenW(name), value, strlenW(value));

    heap_free(name);
    heap_free(value);
    return SUCCEEDED(hres) ? NS_OK : NS_ERROR_UNEXPECTED;
}