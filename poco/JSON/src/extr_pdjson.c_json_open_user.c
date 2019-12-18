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
typedef  void* json_user_io ;
struct TYPE_7__ {void* peek; void* get; void* ptr; } ;
struct TYPE_8__ {TYPE_1__ user; } ;
struct TYPE_9__ {TYPE_2__ source; int /*<<< orphan*/  peek; int /*<<< orphan*/  get; } ;
struct TYPE_10__ {TYPE_3__ source; } ;
typedef  TYPE_4__ json_stream ;

/* Variables and functions */
 int /*<<< orphan*/  init (TYPE_4__*) ; 
 int /*<<< orphan*/  user_get ; 
 int /*<<< orphan*/  user_peek ; 

void json_open_user(json_stream *json, json_user_io get, json_user_io peek, void *user)
{
    init(json);
    json->source.get = user_get;
    json->source.peek = user_peek;
    json->source.source.user.ptr = user;
    json->source.source.user.get = get;
    json->source.source.user.peek = peek;
}