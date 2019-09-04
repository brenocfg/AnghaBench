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
struct TYPE_3__ {int /*<<< orphan*/  start; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ bstr ;
typedef  int /*<<< orphan*/  ASS_Track ;
typedef  int /*<<< orphan*/  ASS_Event ;

/* Variables and functions */
 int /*<<< orphan*/ * add_osd_ass_event (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mangle_ass (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ASS_Event *add_osd_ass_event_escaped(ASS_Track *track, const char *style,
                                            const char *text)
{
    bstr buf = {0};
    mangle_ass(&buf, text);
    ASS_Event *e = add_osd_ass_event(track, style, buf.start);
    talloc_free(buf.start);
    return e;
}