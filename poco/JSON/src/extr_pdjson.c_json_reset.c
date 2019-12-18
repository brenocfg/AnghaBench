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
struct TYPE_3__ {int stack_top; char* errmsg; int /*<<< orphan*/  flags; scalar_t__ ntokens; } ;
typedef  TYPE_1__ json_stream ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_FLAG_ERROR ; 

void json_reset(json_stream *json)
{
    json->stack_top = -1;
    json->ntokens = 0;
    json->flags &= ~JSON_FLAG_ERROR;
    json->errmsg[0] = '\0';
}