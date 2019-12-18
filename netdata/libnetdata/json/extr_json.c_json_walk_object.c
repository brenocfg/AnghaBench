#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t end; size_t start; size_t size; int type; } ;
typedef  TYPE_1__ jsmntok_t ;
struct TYPE_15__ {char* name; char* fullname; char* original_string; int /*<<< orphan*/  (* callback_function ) (TYPE_2__*) ;int /*<<< orphan*/  type; int /*<<< orphan*/ * callback_data; } ;
typedef  TYPE_2__ JSON_ENTRY ;

/* Variables and functions */
#define  JSMN_ARRAY 131 
#define  JSMN_OBJECT 130 
#define  JSMN_PRIMITIVE 129 
#define  JSMN_STRING 128 
 int JSON_FULLNAME_LEN ; 
 int JSON_NAME_LEN ; 
 int /*<<< orphan*/  JSON_OBJECT ; 
 int /*<<< orphan*/  freez (char*) ; 
 size_t json_walk_array (char*,TYPE_1__*,size_t,size_t,TYPE_2__*) ; 
 size_t json_walk_primitive (char*,TYPE_1__*,size_t,TYPE_2__*) ; 
 size_t json_walk_string (char*,TYPE_1__*,size_t,TYPE_2__*) ; 
 char* mallocz (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

size_t json_walk_object(char *js, jsmntok_t *t, size_t nest, size_t start, JSON_ENTRY *e)
{
    JSON_ENTRY ne = {
            .name = "",
            .fullname = "",
            .callback_data = NULL,
            .callback_function = NULL
    };

    char old = js[t[start].end];
    js[t[start].end] = '\0';
    ne.original_string = &js[t[start].start];
    memcpy(&ne, e, sizeof(JSON_ENTRY));
    ne.type = JSON_OBJECT;
    ne.callback_function = NULL;
    if(e->callback_function) e->callback_function(&ne);
    js[t[start].end] = old;

    int key = 1;
    size_t i, init = start, size = t[start].size;

    start++;
    for(i = 0; i < size ; i++) {
        switch(t[start].type) {
            case JSMN_PRIMITIVE:
                start += json_walk_primitive(js, t, start, &ne);
                key = 1;
                break;

            case JSMN_OBJECT:
                start += json_walk_object(js, t, nest + 1, start, &ne);
                key = 1;
                break;

            case JSMN_ARRAY:
                start += json_walk_array(js, t, nest + 1, start, &ne);
                key = 1;
                break;

            case JSMN_STRING:
            default:
                if(key) {
                    int len = t[start].end - t[start].start;
                    if (unlikely(len>JSON_NAME_LEN)) len=JSON_NAME_LEN;
                    strncpy(ne.name, &js[t[start].start], len);
                    ne.name[len] = '\0';
                    len=strlen(e->fullname) + strlen(e->fullname[0]?".":"") + strlen(ne.name);
                    char *c = mallocz((len+1)*sizeof(char));
                    sprintf(c,"%s%s%s", e->fullname, e->fullname[0]?".":"", ne.name);
                    if (unlikely(len>JSON_FULLNAME_LEN)) len=JSON_FULLNAME_LEN;
                    strncpy(ne.fullname, c, len);
                    freez(c);
                    start++;
                    key = 0;
                }
                else {
                    start += json_walk_string(js, t, start, &ne);
                    key = 1;
                }
                break;
        }
    }
    return start - init;
}