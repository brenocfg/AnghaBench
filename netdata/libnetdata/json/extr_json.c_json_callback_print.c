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
struct TYPE_4__ {char* string; int /*<<< orphan*/  boolean; int /*<<< orphan*/  number; int /*<<< orphan*/  items; } ;
struct TYPE_5__ {int type; int (* callback_function ) (TYPE_2__*) ;TYPE_1__ data; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ JSON_ENTRY ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
#define  JSON_ARRAY 133 
#define  JSON_BOOLEAN 132 
#define  JSON_NULL 131 
#define  JSON_NUMBER 130 
#define  JSON_OBJECT 129 
#define  JSON_STRING 128 
 int /*<<< orphan*/ * buffer_create (int) ; 
 int /*<<< orphan*/  buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  buffer_tostring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

int json_callback_print(JSON_ENTRY *e)
{
    BUFFER *wb=buffer_create(300);

    buffer_sprintf(wb,"%s = ", e->name);
    char txt[50];
    switch(e->type) {
        case JSON_OBJECT:
            e->callback_function = json_callback_print;
            buffer_strcat(wb,"OBJECT");
            break;

        case JSON_ARRAY:
            e->callback_function = json_callback_print;
            sprintf(txt,"ARRAY[%lu]", e->data.items);
            buffer_strcat(wb, txt);
            break;

        case JSON_STRING:
            buffer_strcat(wb, e->data.string);
            break;

        case JSON_NUMBER:
            sprintf(txt,"%Lf", e->data.number);
            buffer_strcat(wb,txt);

            break;

        case JSON_BOOLEAN:
            buffer_strcat(wb, e->data.boolean?"TRUE":"FALSE");
            break;

        case JSON_NULL:
            buffer_strcat(wb,"NULL");
            break;
    }
    info("JSON: %s", buffer_tostring(wb));
    buffer_free(wb);
    return 0;
}