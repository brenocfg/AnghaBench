#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int /*<<< orphan*/  chm_file; } ;
struct TYPE_5__ {TYPE_4__ merge; void* local; void* name; } ;
typedef  void* LPWSTR ;
typedef  TYPE_1__ ContentItem ;

/* Variables and functions */
 int /*<<< orphan*/  SetChmPath (TYPE_4__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  _strnicmp (char*,char const*,int) ; 
 int /*<<< orphan*/  debugstr_an (char const*,int) ; 
 void* decode_html (char const*,int,int /*<<< orphan*/ ) ; 
 char* get_attr (char const*,char*,int*) ; 
 int /*<<< orphan*/  heap_free (void*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void parse_obj_node_param(ContentItem *item, ContentItem *hhc_root, const char *text, UINT code_page)
{
    const char *ptr;
    LPWSTR *param, merge;
    int len;

    ptr = get_attr(text, "name", &len);
    if(!ptr) {
        WARN("name attr not found\n");
        return;
    }

    if(!_strnicmp("name", ptr, len)) {
        param = &item->name;
    }else if(!_strnicmp("merge", ptr, len)) {
        param = &merge;
    }else if(!_strnicmp("local", ptr, len)) {
        param = &item->local;
    }else {
        WARN("unhandled param %s\n", debugstr_an(ptr, len));
        return;
    }

    ptr = get_attr(text, "value", &len);
    if(!ptr) {
        WARN("value attr not found\n");
        return;
    }

    /*
     * "merge" parameter data (referencing another CHM file) can be incorporated into the "local" parameter
     * by specifying the filename in the format:
     *  MS-ITS:file.chm::/local_path.htm
     */
    if(param == &item->local && strstr(ptr, "::"))
    {
        const char *local = strstr(ptr, "::")+2;
        int local_len = len-(local-ptr);

        item->local = decode_html(local, local_len, code_page);
        param = &merge;
    }

    *param = decode_html(ptr, len, code_page);

    if(param == &merge) {
        SetChmPath(&item->merge, hhc_root->merge.chm_file, merge);
        heap_free(merge);
    }
}