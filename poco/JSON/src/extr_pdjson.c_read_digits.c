#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* get ) (TYPE_2__*) ;int /*<<< orphan*/  (* peek ) (TYPE_2__*) ;} ;
struct TYPE_6__ {TYPE_2__ source; } ;
typedef  TYPE_1__ json_stream ;

/* Variables and functions */
 scalar_t__ is_digit (int /*<<< orphan*/ ) ; 
 scalar_t__ pushchar (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static int
read_digits(json_stream *json)
{
    unsigned nread = 0;
    while (is_digit(json->source.peek(&json->source))) {
        if (pushchar(json, json->source.get(&json->source)) != 0)
            return -1;

        nread++;
    }

    if (nread == 0) {
        return -1;
    }

    return 0;
}