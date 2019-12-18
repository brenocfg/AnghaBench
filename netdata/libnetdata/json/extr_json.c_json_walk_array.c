#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t end; size_t start; size_t size; int type; } ;
typedef  TYPE_2__ jsmntok_t ;
struct TYPE_15__ {size_t items; } ;
struct TYPE_17__ {char* original_string; char* name; char* fullname; size_t pos; int /*<<< orphan*/  (* callback_function ) (TYPE_3__*) ;TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ JSON_ENTRY ;

/* Variables and functions */
#define  JSMN_ARRAY 131 
#define  JSMN_OBJECT 130 
#define  JSMN_PRIMITIVE 129 
#define  JSMN_STRING 128 
 int /*<<< orphan*/  JSON_ARRAY ; 
 int JSON_FULLNAME_LEN ; 
 int JSON_NAME_LEN ; 
 int /*<<< orphan*/  info (char*,char*,char*) ; 
 size_t json_walk_object (char*,TYPE_2__*,size_t,size_t,TYPE_3__*) ; 
 size_t json_walk_primitive (char*,TYPE_2__*,size_t,TYPE_3__*) ; 
 size_t json_walk_string (char*,TYPE_2__*,size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char*,size_t) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

size_t json_walk_array(char *js, jsmntok_t *t, size_t nest, size_t start, JSON_ENTRY *e)
{
    JSON_ENTRY ne;

    char old = js[t[start].end];
    js[t[start].end] = '\0';
    ne.original_string = &js[t[start].start];

    memcpy(&ne, e, sizeof(JSON_ENTRY));
    ne.type = JSON_ARRAY;
    ne.data.items = t[start].size;
    ne.callback_function = NULL;
    ne.name[0]='\0';
    ne.fullname[0]='\0';
    if(e->callback_function) e->callback_function(&ne);
    js[t[start].end] = old;

    size_t i, init = start, size = t[start].size;

    start++;
    for(i = 0; i < size ; i++) {
        ne.pos = i;
        if (strlen(e->name) > JSON_NAME_LEN  - 24 || strlen(e->fullname) > JSON_FULLNAME_LEN -24) {
            info("JSON: JSON walk_array ignoring element with name:%s fullname:%s",e->name, e->fullname);
            continue;
        }
        snprintfz(ne.name, JSON_NAME_LEN, "%s[%lu]", e->name, i);
        snprintfz(ne.fullname, JSON_FULLNAME_LEN, "%s[%lu]", e->fullname, i);

        switch(t[start].type) {
            case JSMN_PRIMITIVE:
                start += json_walk_primitive(js, t, start, &ne);
                break;

            case JSMN_OBJECT:
                start += json_walk_object(js, t, nest + 1, start, &ne);
                break;

            case JSMN_ARRAY:
                start += json_walk_array(js, t, nest + 1, start, &ne);
                break;

            case JSMN_STRING:
                start += json_walk_string(js, t, start, &ne);
                break;
        }
    }
    return start - init;
}