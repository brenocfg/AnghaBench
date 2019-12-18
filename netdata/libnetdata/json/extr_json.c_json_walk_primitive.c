#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t end; size_t start; } ;
typedef  TYPE_2__ jsmntok_t ;
struct TYPE_7__ {int boolean; int /*<<< orphan*/  number; } ;
struct TYPE_9__ {char* original_string; int /*<<< orphan*/  (* callback_function ) (TYPE_3__*) ;void* type; TYPE_1__ data; } ;
typedef  TYPE_3__ JSON_ENTRY ;

/* Variables and functions */
 void* JSON_BOOLEAN ; 
 void* JSON_NULL ; 
 void* JSON_NUMBER ; 
 int /*<<< orphan*/  strtold (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

size_t json_walk_primitive(char *js, jsmntok_t *t, size_t start, JSON_ENTRY *e)
{
    char old = js[t[start].end];
    js[t[start].end] = '\0';
    e->original_string = &js[t[start].start];

    switch(e->original_string[0]) {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
        case '8': case '9': case '-': case '.':
            e->type = JSON_NUMBER;
            e->data.number = strtold(e->original_string, NULL);
            break;

        case 't': case 'T':
            e->type = JSON_BOOLEAN;
            e->data.boolean = 1;
            break;

        case 'f': case 'F':
            e->type = JSON_BOOLEAN;
            e->data.boolean = 0;
            break;

        case 'n': case 'N':
        default:
            e->type = JSON_NULL;
            break;
    }
    if(e->callback_function) e->callback_function(e);
    js[t[start].end] = old;
    return 1;
}