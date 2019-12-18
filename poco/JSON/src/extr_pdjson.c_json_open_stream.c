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
struct TYPE_7__ {int /*<<< orphan*/ * stream; } ;
struct TYPE_8__ {TYPE_1__ stream; } ;
struct TYPE_9__ {TYPE_2__ source; int /*<<< orphan*/  peek; int /*<<< orphan*/  get; } ;
struct TYPE_10__ {TYPE_3__ source; } ;
typedef  TYPE_4__ json_stream ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  init (TYPE_4__*) ; 
 int /*<<< orphan*/  stream_get ; 
 int /*<<< orphan*/  stream_peek ; 

void json_open_stream(json_stream *json, FILE * stream)
{
    init(json);
    json->source.get = stream_get;
    json->source.peek = stream_peek;
    json->source.source.stream.stream = stream;
}