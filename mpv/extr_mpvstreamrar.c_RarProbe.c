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
struct stream {int dummy; } ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rar_marker ; 
 scalar_t__ rar_marker_size ; 
 TYPE_1__ stream_peek (struct stream*,scalar_t__) ; 

int RarProbe(struct stream *s)
{
    bstr peek = stream_peek(s, rar_marker_size);
    if (peek.len < rar_marker_size)
        return -1;
    if (memcmp(peek.start, rar_marker, rar_marker_size))
        return -1;
    return 0;
}