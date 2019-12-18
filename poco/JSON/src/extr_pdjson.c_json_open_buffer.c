#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* buffer; size_t length; } ;
struct TYPE_8__ {TYPE_1__ buffer; } ;
struct TYPE_9__ {TYPE_2__ source; int /*<<< orphan*/  peek; int /*<<< orphan*/  get; } ;
struct TYPE_10__ {TYPE_3__ source; } ;
typedef  TYPE_4__ json_stream ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_get ; 
 int /*<<< orphan*/  buffer_peek ; 
 int /*<<< orphan*/  init (TYPE_4__*) ; 

void json_open_buffer(json_stream *json, const void *buffer, size_t size)
{
    init(json);
    json->source.get = buffer_get;
    json->source.peek = buffer_peek;
    json->source.source.buffer.buffer = (char*) buffer;
    json->source.source.buffer.length = size;
}