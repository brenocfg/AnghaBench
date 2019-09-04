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
typedef  int /*<<< orphan*/  strbuffer_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  dump_to_strbuffer ; 
 scalar_t__ json_dump_callback (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,size_t) ; 
 char* jsonp_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuffer_close (int /*<<< orphan*/ *) ; 
 scalar_t__ strbuffer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuffer_value (int /*<<< orphan*/ *) ; 

char *json_dumps(const json_t *json, size_t flags)
{
    strbuffer_t strbuff;
    char *result;

    if(strbuffer_init(&strbuff))
        return NULL;

    if(json_dump_callback(json, dump_to_strbuffer, (void *)&strbuff, flags))
        result = NULL;
    else
        result = jsonp_strdup(strbuffer_value(&strbuff));

    strbuffer_close(&strbuff);
    return result;
}