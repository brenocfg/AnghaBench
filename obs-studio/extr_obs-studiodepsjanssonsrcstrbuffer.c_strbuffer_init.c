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
struct TYPE_3__ {char* value; int /*<<< orphan*/  size; scalar_t__ length; } ;
typedef  TYPE_1__ strbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRBUFFER_MIN_SIZE ; 
 char* jsonp_malloc (int /*<<< orphan*/ ) ; 

int strbuffer_init(strbuffer_t *strbuff)
{
    strbuff->size = STRBUFFER_MIN_SIZE;
    strbuff->length = 0;

    strbuff->value = jsonp_malloc(strbuff->size);
    if(!strbuff->value)
        return -1;

    /* initialize to empty */
    strbuff->value[0] = '\0';
    return 0;
}