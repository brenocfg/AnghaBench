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
struct ass_state {TYPE_1__* track; } ;
struct TYPE_7__ {int Encoding; int /*<<< orphan*/  Name; } ;
struct TYPE_6__ {TYPE_2__* styles; } ;
typedef  TYPE_1__ ASS_Track ;
typedef  TYPE_2__ ASS_Style ;

/* Variables and functions */
 int ass_alloc_style (TYPE_1__*) ; 
 int find_style (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static ASS_Style *get_style(struct ass_state *ass, char *name)
{
    ASS_Track *track = ass->track;
    if (!track)
        return NULL;

    int sid = find_style(track, name, -1);
    if (sid >= 0)
        return &track->styles[sid];

    sid = ass_alloc_style(track);
    ASS_Style *style = &track->styles[sid];
    style->Name = strdup(name);
    // Set to neutral base direction, as opposed to VSFilter LTR default
    style->Encoding = -1;
    return style;
}