#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct segment {double end; } ;
struct priv {int duration; int num_segments; struct segment** segments; } ;
struct demuxer {struct priv* priv; } ;

/* Variables and functions */
 int SEEK_FACTOR ; 
 int SEEK_FORWARD ; 
 int SEEK_HR ; 
 int /*<<< orphan*/  switch_segment (struct demuxer*,struct segment*,double,int,int) ; 

__attribute__((used)) static void d_seek(struct demuxer *demuxer, double seek_pts, int flags)
{
    struct priv *p = demuxer->priv;

    double pts = seek_pts * ((flags & SEEK_FACTOR) ? p->duration : 1);

    flags &= SEEK_FORWARD | SEEK_HR;

    struct segment *new = p->segments[p->num_segments - 1];
    for (int n = 0; n < p->num_segments; n++) {
        if (pts < p->segments[n]->end) {
            new = p->segments[n];
            break;
        }
    }

    switch_segment(demuxer, new, pts, flags, false);
}