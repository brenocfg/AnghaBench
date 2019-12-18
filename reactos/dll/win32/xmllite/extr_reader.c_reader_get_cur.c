#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* input; } ;
typedef  TYPE_4__ xmlreader ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {TYPE_2__* buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  cur; } ;
struct TYPE_7__ {TYPE_1__ utf16; } ;

/* Variables and functions */

__attribute__((used)) static inline UINT reader_get_cur(xmlreader *reader)
{
    return reader->input->buffer->utf16.cur;
}