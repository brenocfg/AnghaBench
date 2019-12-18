#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stream; } ;
struct TYPE_4__ {TYPE_1__ stream; } ;
struct json_source {TYPE_2__ source; int /*<<< orphan*/  position; } ;

/* Variables and functions */
 int fgetc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stream_get(struct json_source *source)
{
    source->position++;
    return fgetc(source->source.stream.stream);
}