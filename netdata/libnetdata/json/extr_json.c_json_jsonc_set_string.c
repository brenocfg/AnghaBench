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
struct TYPE_4__ {char* string; } ;
struct TYPE_5__ {int* name; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ JSON_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_STRING ; 
 int /*<<< orphan*/  memcpy (int*,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static inline void json_jsonc_set_string(JSON_ENTRY *e,char *key,const char *value) {
    size_t length = strlen(key);
    e->type = JSON_STRING;
    memcpy(e->name,key,length);
    e->name[length] = 0x00;
    e->data.string = (char *) value;
}