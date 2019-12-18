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
struct json_source {int (* peek ) (struct json_source*) ;int /*<<< orphan*/  position; } ;

/* Variables and functions */
 int stub1 (struct json_source*) ; 

__attribute__((used)) static int buffer_get(struct json_source *source)
{
    int c = source->peek(source);
    source->position++;
    return c;
}