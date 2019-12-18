#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int itemFlags; int nItems; TYPE_1__* items; int /*<<< orphan*/  keyword; } ;
struct TYPE_5__ {int /*<<< orphan*/  local; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_2__ IndexItem ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  _strnicmp (char*,char const*,int) ; 
 int /*<<< orphan*/  debugstr_an (char const*,int) ; 
 int /*<<< orphan*/  decode_html (char const*,int,int /*<<< orphan*/ ) ; 
 char* get_attr (char const*,char*,int*) ; 
 int /*<<< orphan*/  item_realloc (TYPE_2__*,int) ; 

__attribute__((used)) static void parse_index_obj_node_param(IndexItem *item, const char *text, UINT code_page)
{
    const char *ptr;
    LPWSTR *param;
    int len;

    ptr = get_attr(text, "name", &len);
    if(!ptr) {
        WARN("name attr not found\n");
        return;
    }

    /* Allocate a new sub-item, either on the first run or whenever a
     * sub-topic has filled out both the "name" and "local" params.
     */
    if(item->itemFlags == 0x11 && (!_strnicmp("name", ptr, len) || !_strnicmp("local", ptr, len)))
        item_realloc(item, item->nItems+1);
    if(!_strnicmp("keyword", ptr, len)) {
        param = &item->keyword;
    }else if(!item->keyword && !_strnicmp("name", ptr, len)) {
        /* Some HTML Help index files use an additional "name" parameter
         * rather than the "keyword" parameter.  In this case, the first
         * occurrence of the "name" parameter is the keyword.
         */
        param = &item->keyword;
    }else if(!_strnicmp("name", ptr, len)) {
        item->itemFlags |= 0x01;
        param = &item->items[item->nItems-1].name;
    }else if(!_strnicmp("local", ptr, len)) {
        item->itemFlags |= 0x10;
        param = &item->items[item->nItems-1].local;
    }else {
        WARN("unhandled param %s\n", debugstr_an(ptr, len));
        return;
    }

    ptr = get_attr(text, "value", &len);
    if(!ptr) {
        WARN("value attr not found\n");
        return;
    }

    *param = decode_html(ptr, len, code_page);
}